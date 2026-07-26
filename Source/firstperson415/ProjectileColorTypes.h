#pragma once

#include "CoreMinimal.h"
#include "ProjectileColorTypes.generated.h"

/**
 * Data that defines one selectable projectile color and its gameplay effects.
 * Add or tune entries on the character Blueprint without changing projectile code.
 */
USTRUCT(BlueprintType)
struct FProjectileColorDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	FText DisplayName = FText::FromString(TEXT("Standard"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight",
		meta = (ClampMin = "0.1"))
	float SpeedMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact",
		meta = (ClampMin = "0.0"))
	float DirectDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact",
		meta = (ClampMin = "0.0"))
	float PhysicsImpulseMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Impact",
		meta = (ClampMin = "0.1"))
	float ImpactEffectScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain",
		meta = (ClampMin = "0.0"))
	float TerrainRadiusMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terrain",
		meta = (ClampMin = "0.0"))
	float TerrainDepthMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion")
	bool bExplosive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion",
		meta = (EditCondition = "bExplosive", ClampMin = "0.0"))
	float ExplosionRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion",
		meta = (EditCondition = "bExplosive", ClampMin = "0.0"))
	float ExplosionDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explosion",
		meta = (EditCondition = "bExplosive", ClampMin = "0.0"))
	float ExplosionImpulse = 0.0f;
};
