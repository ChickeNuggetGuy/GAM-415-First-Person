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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* ProjectileMat;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Decals,
        meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* BaseMat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile,
        meta = (AllowPrivateAccess = "true"))
    FLinearColor RandColor;

    UPROPERTY(Transient)
    UMaterialInstanceDynamic* DmiMat;

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