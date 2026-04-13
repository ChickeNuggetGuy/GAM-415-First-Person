#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Projectile.generated.h"

class USpereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

/**
 * A paintball-style projectile that splatters a randomly colored decal
 * on impact, spawns a color-matched particle effect, and deforms
 * procedural terrain when hit.
 */
UCLASS(Blueprintable, BlueprintType)
class AProjectile : public AActor
{
    GENERATED_BODY()

public:
    AProjectile();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(
        UPrimitiveComponent* HitComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

    // Base material used to create a dynamic instance with the random color.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* ProjectileMat;

    // Material applied to the splatter decal spawned at the impact point.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Decals,
        meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* BaseMat;

    // Randomly generated color assigned at spawn, shared across the
    // projectile mesh, impact decal, and particle effect for consistency.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    FLinearColor RandColor;

    UPROPERTY(Transient)
    UMaterialInstanceDynamic* DmiMat;

    // Niagara particle system spawned on impact for the paint splash.
    UPROPERTY(EditAnywhere)
    UNiagaraSystem* colorP;

private:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    USphereComponent* CollisionComp;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BallMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement,
        meta = (AllowPrivateAccess = "true"))
    UProjectileMovementComponent* ProjectileMovement;
};