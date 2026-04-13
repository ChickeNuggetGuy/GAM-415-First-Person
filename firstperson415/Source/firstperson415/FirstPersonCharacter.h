// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FirstPersonCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USkeletalMeshComponent;

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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasRifle(bool bNewHasRifle);

	UFUNCTION(BlueprintPure, Category = "Weapon")
	bool GetHasRifle() const;

	UFUNCTION(BlueprintPure, Category = "Components")
	USkeletalMeshComponent* GetMesh1P() const;

	UFUNCTION(BlueprintPure, Category = "Components")
	UCameraComponent* GetFirstPersonCameraComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	bool isTeleporting;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void AddDefaultMappingContext();

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

private:
	UPROPERTY(
		VisibleAnywhere,
		BlueprintReadOnly,
		Category = "Weapon",
		meta = (AllowPrivateAccess = "true"))
	bool bHasRifle;
};