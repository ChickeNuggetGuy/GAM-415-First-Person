// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"
#include "ProjectileColorTypes.h"
#include "FirstPersonCharacter.generated.h"

class UCameraComponent;
class UAnimMontage;
class UInputAction;
class UInputMappingContext;
class USkeletalMesh;
class USkeletalMeshComponent;
class USoundBase;
class UProjectileColorRadialWidget;
class AProjectile;

UCLASS()
class FIRSTPERSON415_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFirstPersonCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(
		UInputComponent* PlayerInputComponent) override;
	virtual void PawnClientRestart() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool GetHasRifle() const;

	UFUNCTION(BlueprintPure, Category = "Components")
	USkeletalMeshComponent* GetMesh1P() const;

	UFUNCTION(BlueprintPure, Category = "Components")
	UCameraComponent* GetFirstPersonCameraComponent() const;

	/** Selects the next entry in ProjectileColors. */
	UFUNCTION(BlueprintCallable, Category = "Projectile Colors")
	void SelectNextProjectileColor();

	/** Selects the previous entry in ProjectileColors. */
	UFUNCTION(BlueprintCallable, Category = "Projectile Colors")
	void SelectPreviousProjectileColor();

	/** Selects an entry directly, wrapping indexes outside the array. */
	UFUNCTION(BlueprintCallable, Category = "Projectile Colors")
	void SelectProjectileColor(int32 NewIndex);

	UFUNCTION(BlueprintPure, Category = "Projectile Colors")
	FProjectileColorDefinition GetSelectedProjectileColor() const;

	UFUNCTION(BlueprintPure, Category = "Projectile Colors")
	int32 GetSelectedProjectileColorIndex() const;

	/** Hook for a Blueprint HUD, weapon material, or audio response. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Colors")
	void ProjectileColorChanged(
		const FProjectileColorDefinition& NewProjectileColor,
		int32 NewIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	bool isTeleporting;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot();
	void AddDefaultMappingContext();
	void AddWeaponMappingContext();
	void TryEquipTemplateRifle(AActor* PickupActor);
	void OpenProjectileColorRadialMenu();
	void CommitProjectileColorRadialMenu();
	void CloseProjectileColorRadialMenu(bool bCommitSelection);

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Camera",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Mesh",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Input",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Input",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Input",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Input",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadWrite,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true"))
	bool bLogInputSetup;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TemplateRiflePickupClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh> TemplateRifleMesh;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> WeaponProjectileClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> WeaponMappingContext;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> FireAnimation;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	FVector ProjectileOffset;

	/**
	 * Available projectile types. Defaults provide explosive red, knockback
	 * blue, terrain-boring green, and fast yellow projectiles.
	 */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile Colors",
		meta = (AllowPrivateAccess = "true", TitleProperty = "DisplayName"))
	TArray<FProjectileColorDefinition> ProjectileColors;

	/** Hold this key to open the radial menu; release it to equip the hover. */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile Colors|Radial Menu",
		meta = (AllowPrivateAccess = "true"))
	FKey ProjectileColorRadialMenuKey;

	/**
	 * Optional UMG subclass for visual customization. The native widget works
	 * without a Widget Blueprint.
	 */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Projectile Colors|Radial Menu",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UProjectileColorRadialWidget>
		ProjectileColorRadialWidgetClass;

private:
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Weapon",
		meta = (AllowPrivateAccess = "true"))
	bool bHasRifle;

	UPROPERTY(
		VisibleInstanceOnly,
		BlueprintReadOnly,
		Category = "Weapon Compatibility",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> EquippedRifle;

	UPROPERTY(
		VisibleInstanceOnly,
		BlueprintReadOnly,
		Category = "Projectile Colors",
		meta = (AllowPrivateAccess = "true"))
	int32 SelectedProjectileColorIndex;

	UPROPERTY(Transient)
	TObjectPtr<UProjectileColorRadialWidget>
		ActiveProjectileColorRadialWidget;

	bool bProjectileColorRadialMenuOpen;
	bool bPreviousShowMouseCursor;
	FVector2D CursorPositionBeforeRadialMenu;

	void InitializeDefaultProjectileColors();
};
