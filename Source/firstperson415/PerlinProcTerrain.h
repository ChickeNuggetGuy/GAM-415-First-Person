#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PerlinProcTerrain.generated.h"

class UMaterialInterface;
class USceneComponent;

/**
 * Higher-resolution procedural terrain split into independently rendered,
 * collided, and updated chunks. A shared vertex grid keeps chunk borders
 * seamless while allowing impacts to rebuild only nearby chunks.
 */
UCLASS()
class FIRSTPERSON415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()

public:
	APerlinProcTerrain();

	virtual void BeginPlay() override;

	/** Number of original terrain cells. ResolutionMultiplier subdivides them. */
	UPROPERTY(EditAnywhere, Category = "Terrain|Resolution",
		meta = (ClampMin = "1"))
	int32 XSize = 100;

	UPROPERTY(EditAnywhere, Category = "Terrain|Resolution",
		meta = (ClampMin = "1"))
	int32 YSize = 100;

	/** Keeps the same footprint while adding more vertices per original cell. */
	UPROPERTY(EditAnywhere, Category = "Terrain|Resolution",
		meta = (ClampMin = "2", ClampMax = "8"))
	int32 ResolutionMultiplier = 2;

	/** Number of quads per independently culled and updated mesh component. */
	UPROPERTY(EditAnywhere, Category = "Terrain|Resolution",
		meta = (ClampMin = "4", ClampMax = "128"))
	int32 ChunkQuads = 32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain|Shape",
		meta = (ClampMin = "0.0"))
	float ZMultiplier = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Terrain|Shape",
		meta = (ClampMin = "0.0001"))
	float noiseScale = 0.1f;

	/** Spacing of the original grid. Subdivision reduces generated spacing. */
	UPROPERTY(EditAnywhere, Category = "Terrain|Resolution",
		meta = (ClampMin = "1.0"))
	float scale = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Terrain|Appearance",
		meta = (ClampMin = "0.0001"))
	float UVScale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Terrain|Impact",
		meta = (ClampMin = "0.0"))
	float radius = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Terrain|Impact")
	FVector Depth = FVector(0.0f, 0.0f, 50.0f);

	UPROPERTY(EditAnywhere, Category = "Terrain|Appearance")
	FLinearColor DefaultTerrainColor =
		FLinearColor(0.18f, 0.32f, 0.08f, 1.0f);

	UPROPERTY(EditAnywhere, Category = "Terrain|Appearance",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float PaintBlendStrength = 0.9f;

	/** Preserves the original deformation-only API. */
	UFUNCTION(BlueprintCallable, Category = "Terrain|Impact")
	void AlterMesh(FVector ImpactPoint);

	/** Preserves deformation-only callers that provide effect multipliers. */
	UFUNCTION(BlueprintCallable, Category = "Terrain|Impact")
	void AlterMeshWithProperties(
		FVector ImpactPoint,
		float RadiusMultiplier,
		float DepthMultiplier);

	/** Deforms and paints the affected vertices using the projectile color. */
	UFUNCTION(BlueprintCallable, Category = "Terrain|Impact")
	void ApplyProjectileImpact(
		FVector ImpactPoint,
		float RadiusMultiplier,
		float DepthMultiplier,
		FLinearColor PaintColor);

	UFUNCTION(BlueprintPure, Category = "Terrain|Debug")
	int32 GetGeneratedChunkCount() const;

	UFUNCTION(BlueprintPure, Category = "Terrain|Debug")
	int32 GetGeneratedVertexCount() const;

	UFUNCTION(BlueprintPure, Category = "Terrain|Debug")
	FVector GetClosestTerrainPoint(FVector WorldLocation) const;

	UFUNCTION(BlueprintPure, Category = "Terrain|Debug")
	FLinearColor GetTerrainColorAtWorldLocation(FVector WorldLocation) const;

	/** Rebuilds the terrain after changing resolution or chunk settings. */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Terrain|Generation")
	void RegenerateTerrain();

protected:
	UPROPERTY(EditAnywhere, Category = "Terrain|Appearance")
	TObjectPtr<UMaterialInterface> Mat;

private:
	struct FTerrainChunk
	{
		UProceduralMeshComponent* Mesh = nullptr;
		int32 StartX = 0;
		int32 StartY = 0;
		int32 QuadsX = 0;
		int32 QuadsY = 0;
	};

	UPROPERTY(VisibleDefaultsOnly, Category = "Terrain")
	TObjectPtr<USceneComponent> TerrainRoot;

	TArray<FTerrainChunk> Chunks;
	TArray<FVector> GridVertices;
	TArray<FColor> GridVertexColors;

	int32 GeneratedQuadsX = 0;
	int32 GeneratedQuadsY = 0;
	float GeneratedSpacing = 100.0f;

	void GenerateTerrain();
	void CreateSharedGrid();
	void CreateChunks();
	void RebuildChunk(FTerrainChunk& Chunk, bool bCreateSection);
	void ModifyTerrain(
		FVector ImpactPoint,
		float RadiusMultiplier,
		float DepthMultiplier,
		const FLinearColor* PaintColor);

	int32 GetGridIndex(int32 GridX, int32 GridY) const;
	FVector CalculateGridNormal(int32 GridX, int32 GridY) const;
};
