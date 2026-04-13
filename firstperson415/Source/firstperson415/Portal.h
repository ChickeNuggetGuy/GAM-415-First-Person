#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UArrowComponent;
class UBoxComponent;
class UMaterialInterface;
class USceneCaptureComponent2D;
class UStaticMeshComponent;
class UTextureRenderTarget2D;

/**
 * A portal actor that teleports pawns to a linked partner portal.
 * Uses a scene capture component to render a live preview of the
 * destination on its mesh surface.
 */
UCLASS()
class FIRSTPERSON415_API APortal : public AActor
{
	GENERATED_BODY()

public:
	APortal();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh;

	// Captures the scene from the player's relative perspective to create
	// the "window into the other side" effect on this portal's surface.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* sceneCapture;

	// Defines the spawn point and facing direction for teleported actors.
	UPROPERTY(EditAnywhere)
	UArrowComponent* rootArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* renderTarget;

	// Overlap volume that triggers teleportation when a pawn enters.
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp;

	// The linked destination portal. Must be set in the editor.
	UPROPERTY(EditAnywhere)
	APortal* OtherPortal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	// Grace period after teleporting to prevent immediate re-trigger.
	UPROPERTY(EditAnywhere, Category = "Portal")
	float TeleportCooldown = 0.5f;

	UFUNCTION()
	void ClearTeleportCooldown(AActor* ActorToClear);

	void UpdatePortals();

private:
	// Actors currently immune to teleportation (recently teleported).
	TSet<AActor*> ActorsInTeleportCooldown;
};