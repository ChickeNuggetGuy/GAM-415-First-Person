#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "ProjectileColorTypes.h"
#include "Projectile.generated.h"

class USpereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

/**
 * A paintball-style projectile that inherits the player's selected color
 * properties, then applies its visual and gameplay effects on impact.
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

    // Selected color shared across the mesh, decal, and particle effect.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    FLinearColor RandColor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    FProjectileColorDefinition ProjectileProperties;

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

    bool bHasImpacted;
};
