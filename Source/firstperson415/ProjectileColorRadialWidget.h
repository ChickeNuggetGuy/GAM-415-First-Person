#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "CoreMinimal.h"
#include "ProjectileColorTypes.h"
#include "ProjectileColorRadialWidget.generated.h"

class UCanvasPanel;
class UTextBlock;
class SProjectileColorWheelSlate;

UCLASS()
class FIRSTPERSON415_API UProjectileColorWheelDisplay : public UWidget
{
	GENERATED_BODY()

public:
	void SetWheelData(
		const TArray<FProjectileColorDefinition>& NewOptions,
		int32 HoveredSelection,
		float NewOuterRadius,
		float NewInnerRadius);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

private:
	void PushStateToSlate();

	TArray<FLinearColor> Colors;
	int32 HoveredIndex = INDEX_NONE;
	float OuterRadius = 246.0f;
	float InnerRadius = 92.0f;

	TSharedPtr<SProjectileColorWheelSlate> WheelSlateWidget;
};

/**
 * Native radial menu used by the first-person character.
 *
 * The widget deliberately builds itself in C++ so the color selector works
 * without requiring an additional binary Widget Blueprint asset. A project can
 * still subclass it in UMG and assign that subclass on the character.
 */
UCLASS(Blueprintable)
class FIRSTPERSON415_API UProjectileColorRadialWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UProjectileColorRadialWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Projectile Colors")
	void SetProjectileColorOptions(
		const TArray<FProjectileColorDefinition>& NewOptions,
		int32 CurrentSelection);

	UFUNCTION(BlueprintPure, Category = "Projectile Colors")
	int32 GetHoveredIndex() const;

	/** Updates the hovered segment immediately instead of waiting for a tick. */
	void RefreshHoverFromCursor();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(
		const FGeometry& MyGeometry,
		float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Menu",
		meta = (ClampMin = "100.0"))
	float MenuRadius = 246.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radial Menu",
		meta = (ClampMin = "0.0"))
	float CenterDeadZoneRadius = 92.0f;

private:
	void BuildBaseLayout();
	void RebuildOptions();
	void RefreshVisuals();
	int32 FindOptionForCursor(const FVector2D& CursorPosition) const;

	UPROPERTY(Transient)
	TObjectPtr<UCanvasPanel> RootCanvas;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> CenterLabel;

	UPROPERTY(Transient)
	TObjectPtr<UTextBlock> CurrentEquippedLabel;

	UPROPERTY(Transient)
	TObjectPtr<UProjectileColorWheelDisplay> WheelDisplay;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UTextBlock>> OptionLabels;

	UPROPERTY(Transient)
	TArray<FProjectileColorDefinition> Options;

	int32 CurrentSelectionIndex = INDEX_NONE;
	int32 HoveredIndex = INDEX_NONE;
};
