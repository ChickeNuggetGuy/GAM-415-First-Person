// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonCharacter.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/SkeletalMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputCoreTypes.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "ProjectileColorRadialWidget.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UnrealType.h"

AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	FirstPersonCameraComponent =
		CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(
		FVector(-10.f, 0.f, 60.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	if (GetMesh())
	{
		GetMesh()->SetOwnerNoSee(true);
		GetMesh()->bCastDynamicShadow = false;
		GetMesh()->CastShadow = false;
	}

	bHasRifle = false;
	isTeleporting = false;
	bLogInputSetup = true;
	SelectedProjectileColorIndex = 0;
	EquippedRifle = nullptr;
	ProjectileOffset = FVector(100.0f, 0.0f, 10.0f);
	ProjectileColorRadialMenuKey = EKeys::Q;
	ProjectileColorRadialWidgetClass =
		UProjectileColorRadialWidget::StaticClass();
	ActiveProjectileColorRadialWidget = nullptr;
	bProjectileColorRadialMenuOpen = false;
	bPreviousShowMouseCursor = false;
	CursorPositionBeforeRadialMenu = FVector2D::ZeroVector;

	static ConstructorHelpers::FClassFinder<AActor> RiflePickupFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_Pickup_Rifle"));
	if (RiflePickupFinder.Succeeded())
	{
		TemplateRiflePickupClass = RiflePickupFinder.Class;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleMeshFinder(
		TEXT("/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if (RifleMeshFinder.Succeeded())
	{
		TemplateRifleMesh = RifleMeshFinder.Object;
	}

	static ConstructorHelpers::FClassFinder<AProjectile> ProjectileFinder(
		TEXT("/Game/Splatter/CustomProjectile"));
	if (ProjectileFinder.Succeeded())
	{
		WeaponProjectileClass = ProjectileFinder.Class;
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		WeaponMappingFinder(
			TEXT("/Game/FirstPerson/Input/IMC_Weapons.IMC_Weapons"));
	if (WeaponMappingFinder.Succeeded())
	{
		WeaponMappingContext = WeaponMappingFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ShootActionFinder(
		TEXT("/Game/FirstPerson/Input/Actions/IA_Shoot.IA_Shoot"));
	if (ShootActionFinder.Succeeded())
	{
		ShootAction = ShootActionFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FireAnimationFinder(
		TEXT("/Game/FirstPersonArms/Animations/FP_Rifle_Shoot_Montage.FP_Rifle_Shoot_Montage"));
	if (FireAnimationFinder.Succeeded())
	{
		FireAnimation = FireAnimationFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> FireSoundFinder(
		TEXT("/Game/FPWeapon/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02"));
	if (FireSoundFinder.Succeeded())
	{
		FireSound = FireSoundFinder.Object;
	}

	InitializeDefaultProjectileColors();
}

void AFirstPersonCharacter::InitializeDefaultProjectileColors()
{
	ProjectileColors.Reset();

	FProjectileColorDefinition Red;
	Red.DisplayName = FText::FromString(TEXT("Red - Explosive"));
	Red.Color = FLinearColor(1.0f, 0.02f, 0.02f);
	Red.SpeedMultiplier = 0.85f;
	Red.DirectDamage = 20.0f;
	Red.PhysicsImpulseMultiplier = 1.5f;
	Red.ImpactEffectScale = 1.6f;
	Red.TerrainRadiusMultiplier = 2.5f;
	Red.TerrainDepthMultiplier = 1.5f;
	Red.bExplosive = true;
	Red.ExplosionRadius = 350.0f;
	Red.ExplosionDamage = 50.0f;
	Red.ExplosionImpulse = 1800.0f;
	ProjectileColors.Add(Red);

	FProjectileColorDefinition Blue;
	Blue.DisplayName = FText::FromString(TEXT("Blue - Knockback"));
	Blue.Color = FLinearColor(0.02f, 0.15f, 1.0f);
	Blue.DirectDamage = 10.0f;
	Blue.PhysicsImpulseMultiplier = 3.0f;
	ProjectileColors.Add(Blue);

	FProjectileColorDefinition Green;
	Green.DisplayName = FText::FromString(TEXT("Green - Terrain Borer"));
	Green.Color = FLinearColor(0.02f, 1.0f, 0.08f);
	Green.DirectDamage = 15.0f;
	Green.ImpactEffectScale = 0.8f;
	Green.TerrainRadiusMultiplier = 0.75f;
	Green.TerrainDepthMultiplier = 2.5f;
	ProjectileColors.Add(Green);

	FProjectileColorDefinition Yellow;
	Yellow.DisplayName = FText::FromString(TEXT("Yellow - High Velocity"));
	Yellow.Color = FLinearColor(1.0f, 0.85f, 0.02f);
	Yellow.SpeedMultiplier = 1.6f;
	Yellow.DirectDamage = 10.0f;
	Yellow.ImpactEffectScale = 0.75f;
	Yellow.TerrainRadiusMultiplier = 0.75f;
	Yellow.TerrainDepthMultiplier = 0.6f;
	ProjectileColors.Add(Yellow);
}

void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	// An older character Blueprint can carry an explicitly empty value for a
	// newly added native array. Keep the runtime selection valid in that case.
	if (ProjectileColors.IsEmpty())
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] Restoring default projectile colors because the Blueprint list is empty"),
			*GetName());
		InitializeDefaultProjectileColors();
	}

	if (bLogInputSetup)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] BeginPlay"), *GetName());
	}

	AddDefaultMappingContext();
}

void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstPersonCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (bLogInputSetup)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] PawnClientRestart"), *GetName());
	}

	AddDefaultMappingContext();

	if (bHasRifle)
	{
		AddWeaponMappingContext();
	}
}

void AFirstPersonCharacter::AddDefaultMappingContext()
{
	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());

	if (!PlayerController)
	{
		if (bLogInputSetup)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s] No PlayerController yet"),
				*GetName());
		}
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		if (bLogInputSetup)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s] No LocalPlayer found"),
				*GetName());
		}
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			LocalPlayer);

	if (!Subsystem)
	{
		if (bLogInputSetup)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s] No Enhanced Input subsystem found"),
				*GetName());
		}
		return;
	}

	if (!DefaultMappingContext)
	{
		if (bLogInputSetup)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("[%s] DefaultMappingContext is not assigned"),
				*GetName());
		}
		return;
	}

	Subsystem->RemoveMappingContext(DefaultMappingContext);
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if (bLogInputSetup)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] Added mapping context: %s"),
			*GetName(),
			*GetNameSafe(DefaultMappingContext.Get()));
	}
}

void AFirstPersonCharacter::AddWeaponMappingContext()
{
	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());
	if (!PlayerController || !WeaponMappingContext)
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			LocalPlayer);
	if (!Subsystem)
	{
		return;
	}

	Subsystem->RemoveMappingContext(WeaponMappingContext);
	Subsystem->AddMappingContext(WeaponMappingContext, 1);
}

void AFirstPersonCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector ForwardDirection =
		FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection =
		FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value)
{
	if (bProjectileColorRadialMenuOpen)
	{
		return;
	}

	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AFirstPersonCharacter::Shoot()
{
	if (bProjectileColorRadialMenuOpen ||
		!bHasRifle ||
		!WeaponProjectileClass ||
		!GetWorld())
	{
		return;
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			FireSound,
			GetActorLocation());
	}

	if (FireAnimation)
	{
		if (UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance())
		{
			AnimInstance->Montage_Play(FireAnimation);
		}
	}

	FRotator SpawnRotation = GetControlRotation();
	FVector CameraLocation = FirstPersonCameraComponent->GetComponentLocation();

	if (const APlayerController* PlayerController =
		Cast<APlayerController>(GetController()))
	{
		if (PlayerController->PlayerCameraManager)
		{
			SpawnRotation =
				PlayerController->PlayerCameraManager->GetCameraRotation();
			CameraLocation =
				PlayerController->PlayerCameraManager->GetCameraLocation();
		}
	}

	const FVector SpawnLocation =
		CameraLocation + SpawnRotation.RotateVector(ProjectileOffset);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	SpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AProjectile>(
		WeaponProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParameters);
}

void AFirstPersonCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (bLogInputSetup)
	{
		UE_LOG(
			LogTemp,
			Log,
			TEXT("[%s] SetupPlayerInputComponent called"),
			*GetName());
	}

	AddDefaultMappingContext();

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInputComponent)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("[%s] Input component is not EnhancedInputComponent"),
			*GetName());
		return;
	}

	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Started,
			this,
			&ACharacter::Jump);

		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Completed,
			this,
			&ACharacter::StopJumping);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] JumpAction is null"), *GetName());
	}

	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			this,
			&AFirstPersonCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] MoveAction is null"), *GetName());
	}

	if (LookAction)
	{
		EnhancedInputComponent->BindAction(
			LookAction,
			ETriggerEvent::Triggered,
			this,
			&AFirstPersonCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] LookAction is null"), *GetName());
	}

	if (ShootAction)
	{
		EnhancedInputComponent->BindAction(
			ShootAction,
			ETriggerEvent::Started,
			this,
			&AFirstPersonCharacter::Shoot);
	}

	// Native key bindings keep this feature independent of binary Enhanced
	// Input assets and make the hold/release behavior available immediately.
	if (ProjectileColorRadialMenuKey.IsValid())
	{
		PlayerInputComponent->BindKey(
			ProjectileColorRadialMenuKey,
			IE_Pressed,
			this,
			&AFirstPersonCharacter::OpenProjectileColorRadialMenu);

		PlayerInputComponent->BindKey(
			ProjectileColorRadialMenuKey,
			IE_Released,
			this,
			&AFirstPersonCharacter::CommitProjectileColorRadialMenu);
	}
}

void AFirstPersonCharacter::OpenProjectileColorRadialMenu()
{
	if (bProjectileColorRadialMenuOpen ||
		ProjectileColors.IsEmpty() ||
		!IsLocallyControlled())
	{
		return;
	}

	APlayerController* PlayerController =
		Cast<APlayerController>(GetController());
	if (!PlayerController || !ProjectileColorRadialWidgetClass)
	{
		return;
	}

	UProjectileColorRadialWidget* RadialWidget =
		CreateWidget<UProjectileColorRadialWidget>(
			PlayerController,
			ProjectileColorRadialWidgetClass);
	if (!RadialWidget)
	{
		return;
	}

	RadialWidget->SetProjectileColorOptions(
		ProjectileColors,
		SelectedProjectileColorIndex);
	RadialWidget->SetDesiredSizeInViewport(FVector2D(680.0f, 680.0f));
	RadialWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.5f));
	RadialWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	RadialWidget->AddToViewport(100);

	bProjectileColorRadialMenuOpen = true;
	ActiveProjectileColorRadialWidget = RadialWidget;
	bPreviousShowMouseCursor = PlayerController->bShowMouseCursor;

	float PreviousMouseX = 0.0f;
	float PreviousMouseY = 0.0f;
	if (PlayerController->GetMousePosition(PreviousMouseX, PreviousMouseY))
	{
		CursorPositionBeforeRadialMenu =
			FVector2D(PreviousMouseX, PreviousMouseY);
	}

	int32 ViewportWidth = 0;
	int32 ViewportHeight = 0;
	PlayerController->GetViewportSize(ViewportWidth, ViewportHeight);
	PlayerController->SetMouseLocation(
		ViewportWidth / 2,
		ViewportHeight / 2);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetIgnoreLookInput(true);

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	PlayerController->SetInputMode(InputMode);
}

void AFirstPersonCharacter::CommitProjectileColorRadialMenu()
{
	CloseProjectileColorRadialMenu(true);
}

void AFirstPersonCharacter::CloseProjectileColorRadialMenu(
	bool bCommitSelection)
{
	if (!bProjectileColorRadialMenuOpen)
	{
		return;
	}

	if (ActiveProjectileColorRadialWidget)
	{
		ActiveProjectileColorRadialWidget->RefreshHoverFromCursor();
		const int32 HoveredIndex =
			ActiveProjectileColorRadialWidget->GetHoveredIndex();
		if (bCommitSelection && ProjectileColors.IsValidIndex(HoveredIndex))
		{
			SelectProjectileColor(HoveredIndex);
		}

		ActiveProjectileColorRadialWidget->RemoveFromParent();
		ActiveProjectileColorRadialWidget = nullptr;
	}

	bProjectileColorRadialMenuOpen = false;

	if (APlayerController* PlayerController =
		Cast<APlayerController>(GetController()))
	{
		// Undo only the ignore request added when this menu opened. Other
		// systems may have their own stacked look-input lock.
		PlayerController->SetIgnoreLookInput(false);
		PlayerController->SetMouseLocation(
			FMath::RoundToInt(CursorPositionBeforeRadialMenu.X),
			FMath::RoundToInt(CursorPositionBeforeRadialMenu.Y));
		PlayerController->bShowMouseCursor = bPreviousShowMouseCursor;

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}

void AFirstPersonCharacter::EndPlay(
	const EEndPlayReason::Type EndPlayReason)
{
	CloseProjectileColorRadialMenu(false);
	Super::EndPlay(EndPlayReason);
}

void AFirstPersonCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	TryEquipTemplateRifle(OtherActor);
}

void AFirstPersonCharacter::TryEquipTemplateRifle(AActor* PickupActor)
{
	if (bHasRifle || !IsValid(PickupActor) ||
		!TemplateRiflePickupClass ||
		!PickupActor->IsA(TemplateRiflePickupClass))
	{
		return;
	}

	if (!TemplateRifleMesh || !Mesh1P)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("[%s] Rifle pickup found, but the rifle mesh is not configured"),
			*GetName());
		return;
	}

	USkeletalMeshComponent* RifleComponent =
		NewObject<USkeletalMeshComponent>(
			this,
			USkeletalMeshComponent::StaticClass(),
			TEXT("EquippedTemplateRifle"));
	if (!RifleComponent)
	{
		return;
	}

	AddInstanceComponent(RifleComponent);
	RifleComponent->SetSkeletalMeshAsset(TemplateRifleMesh);
	RifleComponent->SetOnlyOwnerSee(true);
	RifleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RifleComponent->SetGenerateOverlapEvents(false);
	RifleComponent->bCastDynamicShadow = false;
	RifleComponent->CastShadow = false;
	RifleComponent->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	RifleComponent->RegisterComponent();
	RifleComponent->SetRelativeTransform(FTransform::Identity);

	EquippedRifle = RifleComponent;
	SetHasRifle(true);

	if (UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance())
	{
		if (FBoolProperty* HasRifleProperty =
			FindFProperty<FBoolProperty>(
				AnimInstance->GetClass(),
				TEXT("HasRifle")))
		{
			HasRifleProperty->SetPropertyValue_InContainer(
				AnimInstance,
				true);
		}
	}

	AddWeaponMappingContext();
	PickupActor->Destroy();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("[%s] Equipped the template rifle through native compatibility"),
		*GetName());
}

void AFirstPersonCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AFirstPersonCharacter::GetHasRifle() const
{
	return bHasRifle;
}

USkeletalMeshComponent* AFirstPersonCharacter::GetMesh1P() const
{
	return Mesh1P;
}

UCameraComponent* AFirstPersonCharacter::GetFirstPersonCameraComponent() const
{
	return FirstPersonCameraComponent;
}

void AFirstPersonCharacter::SelectNextProjectileColor()
{
	SelectProjectileColor(SelectedProjectileColorIndex + 1);
}

void AFirstPersonCharacter::SelectPreviousProjectileColor()
{
	SelectProjectileColor(SelectedProjectileColorIndex - 1);
}

void AFirstPersonCharacter::SelectProjectileColor(int32 NewIndex)
{
	if (ProjectileColors.IsEmpty())
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("[%s] ProjectileColors has no entries"),
			*GetName());
		return;
	}

	SelectedProjectileColorIndex =
		((NewIndex % ProjectileColors.Num()) + ProjectileColors.Num()) %
		ProjectileColors.Num();

	const FProjectileColorDefinition& Selection =
		ProjectileColors[SelectedProjectileColorIndex];

	ProjectileColorChanged(Selection, SelectedProjectileColorIndex);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			415,
			1.5f,
			Selection.Color.ToFColor(true),
			FString::Printf(
				TEXT("Projectile: %s"),
				*Selection.DisplayName.ToString()));
	}
}

FProjectileColorDefinition
AFirstPersonCharacter::GetSelectedProjectileColor() const
{
	if (ProjectileColors.IsEmpty())
	{
		return FProjectileColorDefinition();
	}

	const int32 SafeIndex = FMath::Clamp(
		SelectedProjectileColorIndex,
		0,
		ProjectileColors.Num() - 1);
	return ProjectileColors[SafeIndex];
}

int32 AFirstPersonCharacter::GetSelectedProjectileColorIndex() const
{
	return SelectedProjectileColorIndex;
}
