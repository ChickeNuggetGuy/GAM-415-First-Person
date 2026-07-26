#include "Projectile.h"

#include "Components/DecalComponent.h"
#include "Engine/Engine.h"
#include "Engine/OverlapResult.h"
#include "FirstPersonCharacter.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PerlinProcTerrain.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(
        TEXT("SphereComp")
    );
    CollisionComp->InitSphereRadius(20.0f);
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionComp->SetNotifyRigidBodyCollision(true);
    CollisionComp->SetGenerateOverlapEvents(false);
    CollisionComp->SetSimulatePhysics(false);
    CollisionComp->BodyInstance.bUseCCD = true;
    CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

    RootComponent = CollisionComp;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(CollisionComp);
    BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BallMesh->SetGenerateOverlapEvents(false);
    BallMesh->SetSimulatePhysics(false);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
        TEXT("ProjectileComp")
    );
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = 3.0f;

    ProjectileMat = nullptr;
    BaseMat = nullptr;
    DmiMat = nullptr;
    RandColor = FLinearColor::White;
    bHasImpacted = false;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Prefer the explicit spawn relationships, but retain a player-zero
    // fallback for older weapon Blueprints that do not populate Instigator.
    const AFirstPersonCharacter* Character =
        Cast<AFirstPersonCharacter>(GetInstigator());

    if (!Character)
    {
        Character = Cast<AFirstPersonCharacter>(GetOwner());
    }

    if (!Character && GetOwner())
    {
        Character = Cast<AFirstPersonCharacter>(GetOwner()->GetOwner());
    }

    if (!Character)
    {
        Character = Cast<AFirstPersonCharacter>(
            UGameplayStatics::GetPlayerCharacter(this, 0));
    }

    if (Character)
    {
        ProjectileProperties = Character->GetSelectedProjectileColor();
    }
    else
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("[%s] Could not resolve a character; using fallback projectile properties"),
            *GetName());
    }

    RandColor = ProjectileProperties.Color;
    RandColor.A = 1.0f;

    const float SpeedMultiplier =
        FMath::Max(0.1f, ProjectileProperties.SpeedMultiplier);
    ProjectileMovement->InitialSpeed *= SpeedMultiplier;
    ProjectileMovement->MaxSpeed *= SpeedMultiplier;
    ProjectileMovement->Velocity *= SpeedMultiplier;

    if (ProjectileMat)
    {
        DmiMat = UMaterialInstanceDynamic::Create(ProjectileMat, this);

        if (DmiMat)
        {
            BallMesh->SetMaterial(0, DmiMat);
            DmiMat->SetVectorParameterValue(TEXT("ProjColor"), RandColor);
        }
        else
        {
            UE_LOG(
                LogTemp,
                Warning,
                TEXT("Failed to create dynamic material instance for projectile")
            );
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ProjectileMat is null"));
    }
}

void AProjectile::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (bHasImpacted)
    {
        return;
    }

    bHasImpacted = true;
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // Apply this color's direct knockback to the impacted physics object.
    if ((OtherActor != nullptr) && (OtherActor != this) &&
        (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(
            GetVelocity() * 100.0f *
                ProjectileProperties.PhysicsImpulseMultiplier,
            Hit.ImpactPoint
        );
    }

    if (OtherActor != nullptr)
    {
        // Spawn independently in world space so destroying this projectile
        // does not also destroy the attached Niagara component.
        if (colorP)
        {
            UNiagaraComponent* particleComp =
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    colorP,
                    Hit.ImpactPoint + (Hit.ImpactNormal * 2.0f),
                    Hit.ImpactNormal.Rotation()
                );
            if (particleComp)
            {
                particleComp->SetVariableLinearColor(
                    FName("RandomColor"), RandColor
                );
                particleComp->SetWorldScale3D(
                    FVector(ProjectileProperties.ImpactEffectScale));
            }
        }

        APerlinProcTerrain* Procterrain =
            Cast<APerlinProcTerrain>(OtherActor);

        if (Procterrain)
        {
            Procterrain->ApplyProjectileImpact(
                Hit.ImpactPoint,
                ProjectileProperties.TerrainRadiusMultiplier,
                ProjectileProperties.TerrainDepthMultiplier,
                RandColor);
        }

        if (BaseMat)
        {
            const float FrameNum =
                UKismetMathLibrary::RandomFloatInRange(0.f, 3.f);
            const float DecalSize =
                UKismetMathLibrary::RandomFloatInRange(20.f, 40.f) *
                ProjectileProperties.ImpactEffectScale;
            // X is projection depth. Keeping it larger than the visual
            // width lets the decal continue reaching terrain after a crater
            // moves the impacted vertices away from the original surface.
            const FVector ProjectionSize(
                FMath::Max(128.0f, DecalSize * 2.0f),
                DecalSize,
                DecalSize);
            const FVector DecalLocation =
                Hit.ImpactPoint + (Hit.ImpactNormal * 2.0f);
            FRotator DecalRotation = Hit.ImpactNormal.Rotation();
            DecalRotation.Roll =
                UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f);

            UDecalComponent* Decal = nullptr;
            if (OtherComp)
            {
                Decal = UGameplayStatics::SpawnDecalAttached(
                    BaseMat,
                    ProjectionSize,
                    OtherComp,
                    NAME_None,
                    DecalLocation,
                    DecalRotation,
                    EAttachLocation::KeepWorldPosition,
                    0.0f);
            }
            else
            {
                Decal = UGameplayStatics::SpawnDecalAtLocation(
                    GetWorld(),
                    BaseMat,
                    ProjectionSize,
                    DecalLocation,
                    DecalRotation,
                    0.0f);
            }

            if (Decal)
            {
                Decal->SetFadeScreenSize(0.001f);
                Decal->SetSortOrder(1);

                if (UMaterialInstanceDynamic* MatInstance =
                    Decal->CreateDynamicMaterialInstance())
                {
                    MatInstance->SetVectorParameterValue(
                        TEXT("Color"), RandColor);
                    MatInstance->SetScalarParameterValue(
                        TEXT("Frame"), FrameNum);
                    Decal->MarkRenderStateDirty();
                }
                else
                {
                    UE_LOG(
                        LogTemp,
                        Warning,
                        TEXT("[%s] Failed to create decal material instance"),
                        *GetName());
                }
            }
            else
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("[%s] Failed to spawn impact decal"),
                    *GetName());
            }
        }

        if (ProjectileProperties.bExplosive)
        {
            TArray<AActor*> IgnoredActors;
            if (AActor* InstigatorActor = GetInstigator())
            {
                IgnoredActors.Add(InstigatorActor);
            }

            UGameplayStatics::ApplyRadialDamage(
                this,
                ProjectileProperties.ExplosionDamage,
                Hit.ImpactPoint,
                ProjectileProperties.ExplosionRadius,
                UDamageType::StaticClass(),
                IgnoredActors,
                this,
                GetInstigatorController(),
                true);

            FCollisionObjectQueryParams ObjectQuery;
            ObjectQuery.AddObjectTypesToQuery(ECC_PhysicsBody);
            TArray<FOverlapResult> Overlaps;
            FCollisionQueryParams QueryParams(
                SCENE_QUERY_STAT(ProjectileExplosion),
                false,
                this);

            GetWorld()->OverlapMultiByObjectType(
                Overlaps,
                Hit.ImpactPoint,
                FQuat::Identity,
                ObjectQuery,
                FCollisionShape::MakeSphere(
                    ProjectileProperties.ExplosionRadius),
                QueryParams);

            for (const FOverlapResult& Overlap : Overlaps)
            {
                UPrimitiveComponent* Component = Overlap.GetComponent();
                if (Component && Component->IsSimulatingPhysics())
                {
                    Component->AddRadialImpulse(
                        Hit.ImpactPoint,
                        ProjectileProperties.ExplosionRadius,
                        ProjectileProperties.ExplosionImpulse,
                        ERadialImpulseFalloff::RIF_Linear,
                        true);
                }
            }
        }
        else if (ProjectileProperties.DirectDamage > 0.0f)
        {
            UGameplayStatics::ApplyPointDamage(
                OtherActor,
                ProjectileProperties.DirectDamage,
                GetVelocity().GetSafeNormal(),
                Hit,
                GetInstigatorController(),
                this,
                UDamageType::StaticClass());
        }
    }

    BallMesh->SetVisibility(false, true);
    Destroy();
}
