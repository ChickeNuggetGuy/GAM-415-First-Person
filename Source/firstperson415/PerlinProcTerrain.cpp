#include "PerlinProcTerrain.h"

#include "Components/SceneComponent.h"
#include "Materials/MaterialInterface.h"
#include "UObject/UObjectGlobals.h"

APerlinProcTerrain::APerlinProcTerrain()
{
	PrimaryActorTick.bCanEverTick = false;

	TerrainRoot =
		CreateDefaultSubobject<USceneComponent>(TEXT("TerrainRoot"));
	SetRootComponent(TerrainRoot);
}

void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	GenerateTerrain();
}

void APerlinProcTerrain::GenerateTerrain()
{
	for (FTerrainChunk& Chunk : Chunks)
	{
		if (IsValid(Chunk.Mesh))
		{
			Chunk.Mesh->DestroyComponent();
		}
	}

	Chunks.Reset();
	GridVertices.Reset();
	GridVertexColors.Reset();

	const int32 SafeResolution = FMath::Max(2, ResolutionMultiplier);
	GeneratedQuadsX = FMath::Max(1, XSize) * SafeResolution;
	GeneratedQuadsY = FMath::Max(1, YSize) * SafeResolution;
	GeneratedSpacing = FMath::Max(1.0f, scale) / SafeResolution;

	CreateSharedGrid();
	CreateChunks();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("[%s] Generated %d x %d high-resolution terrain in %d chunks (%d shared vertices)"),
		*GetName(),
		GeneratedQuadsX,
		GeneratedQuadsY,
		Chunks.Num(),
		GridVertices.Num());
}

void APerlinProcTerrain::CreateSharedGrid()
{
	const int32 VertexCount =
		(GeneratedQuadsX + 1) * (GeneratedQuadsY + 1);
	GridVertices.Reserve(VertexCount);
	GridVertexColors.Reserve(VertexCount);

	const float SafeResolution =
		static_cast<float>(FMath::Max(2, ResolutionMultiplier));
	const FColor InitialColor = DefaultTerrainColor.ToFColor(false);

	for (int32 X = 0; X <= GeneratedQuadsX; ++X)
	{
		for (int32 Y = 0; Y <= GeneratedQuadsY; ++Y)
		{
			const FVector2D NoisePosition(
				(static_cast<float>(X) / SafeResolution) * noiseScale + 0.1f,
				(static_cast<float>(Y) / SafeResolution) * noiseScale + 0.1f);
			const float Z =
				FMath::PerlinNoise2D(NoisePosition) * ZMultiplier;

			GridVertices.Add(FVector(
				X * GeneratedSpacing,
				Y * GeneratedSpacing,
				Z));
			GridVertexColors.Add(InitialColor);
		}
	}
}

void APerlinProcTerrain::CreateChunks()
{
	const int32 SafeChunkQuads = FMath::Max(4, ChunkQuads);
	const int32 ChunkCountX =
		FMath::DivideAndRoundUp(GeneratedQuadsX, SafeChunkQuads);
	const int32 ChunkCountY =
		FMath::DivideAndRoundUp(GeneratedQuadsY, SafeChunkQuads);

	UMaterialInterface* TerrainMaterial = Mat;
	if (!TerrainMaterial)
	{
		TerrainMaterial = LoadObject<UMaterialInterface>(
			nullptr,
			TEXT("/Game/Materials/M_ProceduralTerrainPaint.M_ProceduralTerrainPaint"));
	}

	Chunks.Reserve(ChunkCountX * ChunkCountY);

	for (int32 ChunkX = 0; ChunkX < ChunkCountX; ++ChunkX)
	{
		for (int32 ChunkY = 0; ChunkY < ChunkCountY; ++ChunkY)
		{
			FTerrainChunk& Chunk = Chunks.AddDefaulted_GetRef();
			Chunk.StartX = ChunkX * SafeChunkQuads;
			Chunk.StartY = ChunkY * SafeChunkQuads;
			Chunk.QuadsX = FMath::Min(
				SafeChunkQuads,
				GeneratedQuadsX - Chunk.StartX);
			Chunk.QuadsY = FMath::Min(
				SafeChunkQuads,
				GeneratedQuadsY - Chunk.StartY);

			const FName ComponentName(*FString::Printf(
				TEXT("TerrainChunk_%d_%d"),
				ChunkX,
				ChunkY));
			Chunk.Mesh = NewObject<UProceduralMeshComponent>(
				this,
				UProceduralMeshComponent::StaticClass(),
				ComponentName);

			if (!Chunk.Mesh)
			{
				continue;
			}

			AddInstanceComponent(Chunk.Mesh);
			Chunk.Mesh->SetupAttachment(TerrainRoot);
			Chunk.Mesh->SetMobility(EComponentMobility::Movable);
			Chunk.Mesh->bUseAsyncCooking = true;
			Chunk.Mesh->SetCollisionEnabled(
				ECollisionEnabled::QueryAndPhysics);
			Chunk.Mesh->SetCollisionResponseToAllChannels(ECR_Block);
			Chunk.Mesh->RegisterComponent();

			RebuildChunk(Chunk, true);
			if (TerrainMaterial)
			{
				Chunk.Mesh->SetMaterial(0, TerrainMaterial);
			}
		}
	}
}

void APerlinProcTerrain::RebuildChunk(
	FTerrainChunk& Chunk,
	bool bCreateSection)
{
	if (!IsValid(Chunk.Mesh))
	{
		return;
	}

	const int32 LocalVertexCount =
		(Chunk.QuadsX + 1) * (Chunk.QuadsY + 1);
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	Vertices.Reserve(LocalVertexCount);
	UVs.Reserve(LocalVertexCount);
	Normals.Reserve(LocalVertexCount);
	VertexColors.Reserve(LocalVertexCount);
	Tangents.Reserve(LocalVertexCount);
	Triangles.Reserve(Chunk.QuadsX * Chunk.QuadsY * 6);

	const float SafeResolution =
		static_cast<float>(FMath::Max(2, ResolutionMultiplier));

	for (int32 LocalX = 0; LocalX <= Chunk.QuadsX; ++LocalX)
	{
		for (int32 LocalY = 0; LocalY <= Chunk.QuadsY; ++LocalY)
		{
			const int32 GridX = Chunk.StartX + LocalX;
			const int32 GridY = Chunk.StartY + LocalY;
			const int32 GridIndex = GetGridIndex(GridX, GridY);

			Vertices.Add(GridVertices[GridIndex]);
			VertexColors.Add(GridVertexColors[GridIndex]);
			Normals.Add(CalculateGridNormal(GridX, GridY));
			UVs.Add(FVector2D(
				(static_cast<float>(GridX) / SafeResolution) * UVScale,
				(static_cast<float>(GridY) / SafeResolution) * UVScale));

			const int32 LeftX = FMath::Max(0, GridX - 1);
			const int32 RightX = FMath::Min(GeneratedQuadsX, GridX + 1);
			const FVector TangentDirection =
				GridVertices[GetGridIndex(RightX, GridY)] -
				GridVertices[GetGridIndex(LeftX, GridY)];
			Tangents.Add(FProcMeshTangent(
				TangentDirection.GetSafeNormal(),
				false));
		}
	}

	const int32 RowSize = Chunk.QuadsY + 1;
	for (int32 LocalX = 0; LocalX < Chunk.QuadsX; ++LocalX)
	{
		for (int32 LocalY = 0; LocalY < Chunk.QuadsY; ++LocalY)
		{
			const int32 Vertex = LocalX * RowSize + LocalY;
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + RowSize);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + RowSize + 1);
			Triangles.Add(Vertex + RowSize);
		}
	}

	if (bCreateSection)
	{
		Chunk.Mesh->CreateMeshSection(
			0,
			Vertices,
			Triangles,
			Normals,
			UVs,
			VertexColors,
			Tangents,
			true);
	}
	else
	{
		Chunk.Mesh->UpdateMeshSection(
			0,
			Vertices,
			Normals,
			UVs,
			VertexColors,
			Tangents);
	}
}

void APerlinProcTerrain::AlterMesh(FVector ImpactPoint)
{
	ModifyTerrain(ImpactPoint, 1.0f, 1.0f, nullptr);
}

void APerlinProcTerrain::AlterMeshWithProperties(
	FVector ImpactPoint,
	float RadiusMultiplier,
	float DepthMultiplier)
{
	ModifyTerrain(
		ImpactPoint,
		RadiusMultiplier,
		DepthMultiplier,
		nullptr);
}

void APerlinProcTerrain::ApplyProjectileImpact(
	FVector ImpactPoint,
	float RadiusMultiplier,
	float DepthMultiplier,
	FLinearColor PaintColor)
{
	PaintColor.A = 1.0f;
	ModifyTerrain(
		ImpactPoint,
		RadiusMultiplier,
		DepthMultiplier,
		&PaintColor);
}

void APerlinProcTerrain::ModifyTerrain(
	FVector ImpactPoint,
	float RadiusMultiplier,
	float DepthMultiplier,
	const FLinearColor* PaintColor)
{
	if (GridVertices.IsEmpty())
	{
		return;
	}

	const float EffectRadius =
		radius * FMath::Max(0.0f, RadiusMultiplier);
	if (EffectRadius <= UE_KINDA_SMALL_NUMBER)
	{
		return;
	}

	const FVector LocalImpactPoint =
		GetActorTransform().InverseTransformPosition(ImpactPoint);
	const int32 MinX = FMath::Clamp(
		FMath::FloorToInt(
			(LocalImpactPoint.X - EffectRadius) / GeneratedSpacing),
		0,
		GeneratedQuadsX);
	const int32 MaxX = FMath::Clamp(
		FMath::CeilToInt(
			(LocalImpactPoint.X + EffectRadius) / GeneratedSpacing),
		0,
		GeneratedQuadsX);
	const int32 MinY = FMath::Clamp(
		FMath::FloorToInt(
			(LocalImpactPoint.Y - EffectRadius) / GeneratedSpacing),
		0,
		GeneratedQuadsY);
	const int32 MaxY = FMath::Clamp(
		FMath::CeilToInt(
			(LocalImpactPoint.Y + EffectRadius) / GeneratedSpacing),
		0,
		GeneratedQuadsY);

	bool bChanged = false;
	for (int32 GridX = MinX; GridX <= MaxX; ++GridX)
	{
		for (int32 GridY = MinY; GridY <= MaxY; ++GridY)
		{
			const int32 GridIndex = GetGridIndex(GridX, GridY);
			const float Distance =
				FVector::Distance(GridVertices[GridIndex], LocalImpactPoint);
			if (Distance >= EffectRadius)
			{
				continue;
			}

			const float Falloff =
				FMath::Square(1.0f - (Distance / EffectRadius));
			GridVertices[GridIndex] -=
				Depth * FMath::Max(0.0f, DepthMultiplier) * Falloff;

			if (PaintColor)
			{
				const FLinearColor ExistingColor =
					GridVertexColors[GridIndex].ReinterpretAsLinear();
				const float BlendAmount = FMath::Clamp(
					PaintBlendStrength * FMath::Max(0.2f, Falloff),
					0.0f,
					1.0f);
				FLinearColor BlendedColor = FMath::Lerp(
					ExistingColor,
					*PaintColor,
					BlendAmount);
				BlendedColor.A = 1.0f;
				GridVertexColors[GridIndex] =
					BlendedColor.ToFColor(false);
			}

			bChanged = true;
		}
	}

	if (!bChanged)
	{
		return;
	}

	// Include one extra grid vertex so normals on adjacent chunk borders
	// are rebuilt from the modified shared height data.
	const int32 DirtyMinX = FMath::Max(0, MinX - 1);
	const int32 DirtyMaxX = FMath::Min(GeneratedQuadsX, MaxX + 1);
	const int32 DirtyMinY = FMath::Max(0, MinY - 1);
	const int32 DirtyMaxY = FMath::Min(GeneratedQuadsY, MaxY + 1);

	for (FTerrainChunk& Chunk : Chunks)
	{
		const int32 ChunkMaxX = Chunk.StartX + Chunk.QuadsX;
		const int32 ChunkMaxY = Chunk.StartY + Chunk.QuadsY;
		const bool bOverlapsDirtyArea =
			Chunk.StartX <= DirtyMaxX &&
			ChunkMaxX >= DirtyMinX &&
			Chunk.StartY <= DirtyMaxY &&
			ChunkMaxY >= DirtyMinY;

		if (bOverlapsDirtyArea)
		{
			RebuildChunk(Chunk, false);
		}
	}
}

int32 APerlinProcTerrain::GetGridIndex(
	int32 GridX,
	int32 GridY) const
{
	return GridX * (GeneratedQuadsY + 1) + GridY;
}

FVector APerlinProcTerrain::CalculateGridNormal(
	int32 GridX,
	int32 GridY) const
{
	const int32 LeftX = FMath::Max(0, GridX - 1);
	const int32 RightX = FMath::Min(GeneratedQuadsX, GridX + 1);
	const int32 DownY = FMath::Max(0, GridY - 1);
	const int32 UpY = FMath::Min(GeneratedQuadsY, GridY + 1);

	const FVector TangentX =
		GridVertices[GetGridIndex(RightX, GridY)] -
		GridVertices[GetGridIndex(LeftX, GridY)];
	const FVector TangentY =
		GridVertices[GetGridIndex(GridX, UpY)] -
		GridVertices[GetGridIndex(GridX, DownY)];
	return FVector::CrossProduct(TangentX, TangentY).GetSafeNormal();
}

int32 APerlinProcTerrain::GetGeneratedChunkCount() const
{
	return Chunks.Num();
}

int32 APerlinProcTerrain::GetGeneratedVertexCount() const
{
	return GridVertices.Num();
}

FVector APerlinProcTerrain::GetClosestTerrainPoint(
	FVector WorldLocation) const
{
	if (GridVertices.IsEmpty())
	{
		return GetActorLocation();
	}

	const FVector LocalLocation =
		GetActorTransform().InverseTransformPosition(WorldLocation);
	const int32 GridX = FMath::Clamp(
		FMath::RoundToInt(LocalLocation.X / GeneratedSpacing),
		0,
		GeneratedQuadsX);
	const int32 GridY = FMath::Clamp(
		FMath::RoundToInt(LocalLocation.Y / GeneratedSpacing),
		0,
		GeneratedQuadsY);
	return GetActorTransform().TransformPosition(
		GridVertices[GetGridIndex(GridX, GridY)]);
}

FLinearColor APerlinProcTerrain::GetTerrainColorAtWorldLocation(
	FVector WorldLocation) const
{
	if (GridVertexColors.IsEmpty())
	{
		return FLinearColor::Transparent;
	}

	const FVector LocalLocation =
		GetActorTransform().InverseTransformPosition(WorldLocation);
	const int32 GridX = FMath::Clamp(
		FMath::RoundToInt(LocalLocation.X / GeneratedSpacing),
		0,
		GeneratedQuadsX);
	const int32 GridY = FMath::Clamp(
		FMath::RoundToInt(LocalLocation.Y / GeneratedSpacing),
		0,
		GeneratedQuadsY);
	return GridVertexColors[
		GetGridIndex(GridX, GridY)].ReinterpretAsLinear();
}

void APerlinProcTerrain::RegenerateTerrain()
{
	GenerateTerrain();
}
