#include "Portal.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = boxComp;
	boxComp->InitBoxExtent(FVector(150.f, 150.f, 150.f));

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(
		TEXT("Capture"));
	sceneCapture->SetupAttachment(RootComponent);

	rootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("RootArrow"));
	rootArrow->SetupAttachment(RootComponent);

	TeleportCooldown = 0.5f;
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	boxComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	boxComp->SetGenerateOverlapEvents(true);

	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}

	if (renderTarget && sceneCapture)
	{
		sceneCapture->TextureTarget = renderTarget;
	}

	// Hide this portal's mesh from its own scene capture so it doesn't
	// appear recursively in the render target.
	mesh->SetHiddenInSceneCapture(true);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] BeginPlay. OtherPortal = %s. BoxExtent = %s"),
		*GetName(),
		*GetNameSafe(OtherPortal),
		*boxComp->GetScaledBoxExtent().ToString());

	DrawDebugBox(
		GetWorld(),
		boxComp->GetComponentLocation(),
		boxComp->GetScaledBoxExtent(),
		boxComp->GetComponentQuat(),
		FColor::Green,
		true,
		30.0f,
		0,
		3.0f);
}

void APortal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] NotifyActorBeginOverlap: %s"),
		*GetName(),
		*GetNameSafe(OtherActor));

	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] Overlapping actor is not a pawn"),
			*GetName());
		return;
	}

	if (!OtherPortal)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] OtherPortal is null"),
			*GetName());
		return;
	}

	// Skip if either portal still has this pawn on cooldown to prevent
	// infinite teleport loops between the two portals.
	if (ActorsInTeleportCooldown.Contains(PlayerPawn) ||
		OtherPortal->ActorsInTeleportCooldown.Contains(PlayerPawn))
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] Pawn is in teleport cooldown"),
			*GetName());
		return;
	}

	// Mark the pawn as cooling down on both portals before teleporting.
	ActorsInTeleportCooldown.Add(PlayerPawn);
	OtherPortal->ActorsInTeleportCooldown.Add(PlayerPawn);

	// Use the arrow component for precise exit placement, falling back
	// to the portal's own transform if no arrow is set.
	const FVector TargetLocation =
		OtherPortal->rootArrow
		? OtherPortal->rootArrow->GetComponentLocation()
		: OtherPortal->GetActorLocation();

	const FRotator TargetRotation =
		OtherPortal->rootArrow
		? OtherPortal->rootArrow->GetComponentRotation()
		: OtherPortal->GetActorRotation();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[%s] Teleporting %s to %s"),
		*GetName(),
		*GetNameSafe(PlayerPawn),
		*TargetLocation.ToString());

	PlayerPawn->TeleportTo(TargetLocation, TargetRotation);

	// Schedule cooldown removal on both portals so the pawn can
	// teleport again after the grace period expires.
	FTimerHandle ThisHandle;
	FTimerDelegate ThisDelegate;
	ThisDelegate.BindUFunction(
		this,
		FName("ClearTeleportCooldown"),
		Cast<AActor>(PlayerPawn));
	GetWorld()->GetTimerManager().SetTimer(
		ThisHandle,
		ThisDelegate,
		TeleportCooldown,
		false);

	FTimerHandle OtherHandle;
	FTimerDelegate OtherDelegate;
	OtherDelegate.BindUFunction(
		OtherPortal,
		FName("ClearTeleportCooldown"),
		Cast<AActor>(PlayerPawn));
	GetWorld()->GetTimerManager().SetTimer(
		OtherHandle,
		OtherDelegate,
		TeleportCooldown,
		false);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePortals();

	ACharacter* PlayerCharacter =
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter &&
		boxComp->IsOverlappingActor(PlayerCharacter))
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] TICK: Player IS overlapping box right now"),
			*GetName());
	}
}

void APortal::ClearTeleportCooldown(AActor* ActorToClear)
{
	if (!ActorToClear)
	{
		return;
	}

	ActorsInTeleportCooldown.Remove(ActorToClear);
}

/**
 * Mirrors the player camera's position relative to the linked portal
 * onto this portal's scene capture, producing a perspective-correct
 * live preview of the destination.
 */
void APortal::UpdatePortals()
{
	if (!OtherPortal || !sceneCapture)
	{
		return;
	}

	APlayerCameraManager* CameraManager =
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	if (!CameraManager)
	{
		return;
	}

	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FRotator CameraRotation = CameraManager->GetCameraRotation();

	// Offset the capture by the same amount the camera is offset from
	// the other portal, so the view matches what you'd see walking through.
	const FVector LocationOffset =
		CameraLocation - OtherPortal->GetActorLocation();

	sceneCapture->SetWorldLocationAndRotation(
		GetActorLocation() + LocationOffset,
		CameraRotation);
}