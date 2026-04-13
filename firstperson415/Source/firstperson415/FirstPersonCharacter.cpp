// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"

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
}

void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

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
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller == nullptr)
	{
		return;
	}

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
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