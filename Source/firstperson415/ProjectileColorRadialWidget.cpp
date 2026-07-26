#include "ProjectileColorRadialWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Framework/Application/SlateApplication.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Widgets/SLeafWidget.h"

namespace ProjectileColorRadialMenu
{
	constexpr float WidgetSize = 680.0f;
	constexpr float Center = WidgetSize * 0.5f;
	constexpr float LabelRadiusRatio = 0.56f;
	constexpr float MinimumAngularGap = 0.018f;
	constexpr float MaximumAngularGap = 0.045f;

	FVector2D DirectionForAngle(float Angle)
	{
		return FVector2D(FMath::Cos(Angle), FMath::Sin(Angle));
	}

	FLinearColor Brighten(const FLinearColor& Color, float Multiplier)
	{
		return FLinearColor(
			FMath::Min(Color.R * Multiplier, 1.0f),
			FMath::Min(Color.G * Multiplier, 1.0f),
			FMath::Min(Color.B * Multiplier, 1.0f),
			Color.A);
	}

	void AddVertex(
		TArray<FSlateVertex>& Vertices,
		const FGeometry& Geometry,
		const FVector2D& LocalPosition,
		const FLinearColor& Color)
	{
		const FVector2D AbsolutePosition =
			Geometry.LocalToAbsolute(LocalPosition);
		FSlateVertex& Vertex = Vertices.AddDefaulted_GetRef();
		Vertex.Position[0] = static_cast<float>(AbsolutePosition.X);
		Vertex.Position[1] = static_cast<float>(AbsolutePosition.Y);
		Vertex.TexCoords[0] = 0.5f;
		Vertex.TexCoords[1] = 0.5f;
		Vertex.TexCoords[2] = 1.0f;
		Vertex.TexCoords[3] = 1.0f;
		Vertex.Color = Color.ToFColor(true);
	}

	void DrawAnnularSector(
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FGeometry& Geometry,
		const FVector2D& CenterPosition,
		float InnerRadius,
		float OuterRadius,
		float StartAngle,
		float EndAngle,
		const FLinearColor& Color)
	{
		const float AngularSpan = FMath::Abs(EndAngle - StartAngle);
		const int32 ArcSegments = FMath::Max(
			3,
			FMath::CeilToInt(AngularSpan / FMath::DegreesToRadians(4.0f)));

		TArray<FSlateVertex> Vertices;
		TArray<SlateIndex> Indices;
		Vertices.Reserve((ArcSegments + 1) * 2);
		Indices.Reserve(ArcSegments * 6);

		for (int32 Segment = 0; Segment <= ArcSegments; ++Segment)
		{
			const float Alpha =
				static_cast<float>(Segment) / static_cast<float>(ArcSegments);
			const float Angle = FMath::Lerp(StartAngle, EndAngle, Alpha);
			const FVector2D Direction = DirectionForAngle(Angle);
			AddVertex(
				Vertices,
				Geometry,
				CenterPosition + Direction * InnerRadius,
				Color);
			AddVertex(
				Vertices,
				Geometry,
				CenterPosition + Direction * OuterRadius,
				Color);
		}

		for (int32 Segment = 0; Segment < ArcSegments; ++Segment)
		{
			const SlateIndex InnerA = static_cast<SlateIndex>(Segment * 2);
			const SlateIndex OuterA = InnerA + 1;
			const SlateIndex InnerB = InnerA + 2;
			const SlateIndex OuterB = InnerA + 3;

			Indices.Add(InnerA);
			Indices.Add(OuterA);
			Indices.Add(OuterB);
			Indices.Add(InnerA);
			Indices.Add(OuterB);
			Indices.Add(InnerB);
		}

		const FSlateBrush* WhiteBrush =
			FCoreStyle::Get().GetBrush(TEXT("WhiteBrush"));
		FSlateDrawElement::MakeCustomVerts(
			OutDrawElements,
			LayerId,
			WhiteBrush->GetRenderingResource(),
			Vertices,
			Indices,
			nullptr,
			0,
			0);
	}

	void DrawArc(
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FGeometry& Geometry,
		const FVector2D& CenterPosition,
		float Radius,
		float StartAngle,
		float EndAngle,
		const FLinearColor& Color,
		float Thickness)
	{
		const float AngularSpan = FMath::Abs(EndAngle - StartAngle);
		const int32 ArcSegments = FMath::Max(
			12,
			FMath::CeilToInt(AngularSpan / FMath::DegreesToRadians(4.0f)));
		TArray<FVector2D> Points;
		Points.Reserve(ArcSegments + 1);

		for (int32 Segment = 0; Segment <= ArcSegments; ++Segment)
		{
			const float Alpha =
				static_cast<float>(Segment) / static_cast<float>(ArcSegments);
			const float Angle = FMath::Lerp(StartAngle, EndAngle, Alpha);
			Points.Add(
				CenterPosition + DirectionForAngle(Angle) * Radius);
		}

		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			Geometry.ToPaintGeometry(),
			Points,
			ESlateDrawEffect::None,
			Color,
			true,
			Thickness);
	}
}

class SProjectileColorWheelSlate : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SProjectileColorWheelSlate)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		SetCanTick(false);
	}

	void SetWheelData(
		const TArray<FLinearColor>& NewColors,
		int32 NewHoveredSelection,
		float NewOuterRadius,
		float NewInnerRadius)
	{
		Colors = NewColors;
		HoveredIndex = NewHoveredSelection;
		OuterRadius = NewOuterRadius;
		InnerRadius = NewInnerRadius;
		Invalidate(EInvalidateWidgetReason::Paint);
	}

	virtual FVector2D ComputeDesiredSize(
		float LayoutScaleMultiplier) const override
	{
		return FVector2D(
			ProjectileColorRadialMenu::WidgetSize,
			ProjectileColorRadialMenu::WidgetSize);
	}

	virtual int32 OnPaint(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override
	{
		const FVector2D CenterPosition =
			AllottedGeometry.GetLocalSize() * 0.5f;
		const float FullCircle = 2.0f * PI;

		ProjectileColorRadialMenu::DrawAnnularSector(
			OutDrawElements,
			LayerId,
			AllottedGeometry,
			CenterPosition + FVector2D(0.0f, 7.0f),
			0.0f,
			OuterRadius + 25.0f,
			0.0f,
			FullCircle,
			FLinearColor(0.0f, 0.0f, 0.0f, 0.42f));
		ProjectileColorRadialMenu::DrawAnnularSector(
			OutDrawElements,
			LayerId + 1,
			AllottedGeometry,
			CenterPosition,
			0.0f,
			OuterRadius + 18.0f,
			0.0f,
			FullCircle,
			FLinearColor(0.012f, 0.018f, 0.032f, 0.94f));
		ProjectileColorRadialMenu::DrawAnnularSector(
			OutDrawElements,
			LayerId + 2,
			AllottedGeometry,
			CenterPosition,
			OuterRadius + 4.0f,
			OuterRadius + 10.0f,
			0.0f,
			FullCircle,
			FLinearColor(0.38f, 0.43f, 0.54f, 0.72f));

		if (!Colors.IsEmpty())
		{
			const float AngleStep =
				FullCircle / static_cast<float>(Colors.Num());
			const float Gap = FMath::Clamp(
				AngleStep * 0.035f,
				ProjectileColorRadialMenu::MinimumAngularGap,
				ProjectileColorRadialMenu::MaximumAngularGap);

			for (int32 Index = 0; Index < Colors.Num(); ++Index)
			{
				const float CenterAngle =
					-0.5f * PI + AngleStep * static_cast<float>(Index);
				const float StartAngle =
					CenterAngle - AngleStep * 0.5f + Gap;
				const float EndAngle =
					CenterAngle + AngleStep * 0.5f - Gap;
				const bool bHovered = Index == HoveredIndex;

				if (bHovered)
				{
					FLinearColor GlowColor = Colors[Index];
					GlowColor.A = 0.30f;
					ProjectileColorRadialMenu::DrawAnnularSector(
						OutDrawElements,
						LayerId + 3,
						AllottedGeometry,
						CenterPosition,
						InnerRadius - 7.0f,
						OuterRadius + 14.0f,
						StartAngle - 0.012f,
						EndAngle + 0.012f,
						GlowColor);
				}

				FLinearColor SegmentColor =
					ProjectileColorRadialMenu::Brighten(
						Colors[Index],
						bHovered ? 1.38f : 0.72f);
				SegmentColor.A = bHovered ? 1.0f : 0.82f;

				ProjectileColorRadialMenu::DrawAnnularSector(
					OutDrawElements,
					LayerId + 4,
					AllottedGeometry,
					CenterPosition,
					InnerRadius + 3.0f,
					OuterRadius,
					StartAngle,
					EndAngle,
					SegmentColor);

				if (bHovered)
				{
					const FLinearColor HoverOutline(
						1.0f,
						1.0f,
						1.0f,
						0.98f);
					ProjectileColorRadialMenu::DrawArc(
						OutDrawElements,
						LayerId + 5,
						AllottedGeometry,
						CenterPosition,
						OuterRadius + 2.0f,
						StartAngle,
						EndAngle,
						HoverOutline,
						4.0f);
					ProjectileColorRadialMenu::DrawArc(
						OutDrawElements,
						LayerId + 5,
						AllottedGeometry,
						CenterPosition,
						InnerRadius + 1.0f,
						StartAngle,
						EndAngle,
						HoverOutline,
						3.0f);
				}
			}

			for (int32 Index = 0; Index < Colors.Num(); ++Index)
			{
				const float BoundaryAngle =
					-0.5f * PI -
					AngleStep * 0.5f +
					AngleStep * static_cast<float>(Index);
				const FVector2D Direction =
					ProjectileColorRadialMenu::DirectionForAngle(
						BoundaryAngle);
				TArray<FVector2D> SeparatorPoints;
				SeparatorPoints.Add(
					CenterPosition + Direction * (InnerRadius + 1.0f));
				SeparatorPoints.Add(
					CenterPosition + Direction * (OuterRadius + 3.0f));
				FSlateDrawElement::MakeLines(
					OutDrawElements,
					LayerId + 6,
					AllottedGeometry.ToPaintGeometry(),
					SeparatorPoints,
					ESlateDrawEffect::None,
					FLinearColor(0.008f, 0.012f, 0.022f, 0.95f),
					true,
					3.0f);
			}
		}

		ProjectileColorRadialMenu::DrawAnnularSector(
			OutDrawElements,
			LayerId + 7,
			AllottedGeometry,
			CenterPosition,
			0.0f,
			InnerRadius - 2.0f,
			0.0f,
			FullCircle,
			FLinearColor(0.018f, 0.025f, 0.043f, 0.98f));
		ProjectileColorRadialMenu::DrawArc(
			OutDrawElements,
			LayerId + 8,
			AllottedGeometry,
			CenterPosition,
			InnerRadius,
			0.0f,
			FullCircle,
			FLinearColor(0.68f, 0.73f, 0.84f, 0.82f),
			3.0f);
		ProjectileColorRadialMenu::DrawArc(
			OutDrawElements,
			LayerId + 8,
			AllottedGeometry,
			CenterPosition,
			OuterRadius + 8.0f,
			0.0f,
			FullCircle,
			FLinearColor(0.78f, 0.82f, 0.9f, 0.86f),
			2.0f);

		return LayerId + 8;
	}

private:
	TArray<FLinearColor> Colors;
	int32 HoveredIndex = INDEX_NONE;
	float OuterRadius = 246.0f;
	float InnerRadius = 92.0f;
};

void UProjectileColorWheelDisplay::SetWheelData(
	const TArray<FProjectileColorDefinition>& NewOptions,
	int32 HoveredSelection,
	float NewOuterRadius,
	float NewInnerRadius)
{
	Colors.Reset(NewOptions.Num());
	for (const FProjectileColorDefinition& Option : NewOptions)
	{
		Colors.Add(Option.Color);
	}

	HoveredIndex = HoveredSelection;
	OuterRadius = NewOuterRadius;
	InnerRadius = NewInnerRadius;
	PushStateToSlate();
}

TSharedRef<SWidget> UProjectileColorWheelDisplay::RebuildWidget()
{
	SAssignNew(WheelSlateWidget, SProjectileColorWheelSlate);
	PushStateToSlate();
	return WheelSlateWidget.ToSharedRef();
}

void UProjectileColorWheelDisplay::ReleaseSlateResources(
	bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	WheelSlateWidget.Reset();
}

void UProjectileColorWheelDisplay::PushStateToSlate()
{
	if (WheelSlateWidget.IsValid())
	{
		WheelSlateWidget->SetWheelData(
			Colors,
			HoveredIndex,
			OuterRadius,
			InnerRadius);
	}
}

UProjectileColorRadialWidget::UProjectileColorRadialWidget(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(false);
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UProjectileColorRadialWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BuildBaseLayout();
}

void UProjectileColorRadialWidget::BuildBaseLayout()
{
	if (!WidgetTree || RootCanvas)
	{
		return;
	}

	RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(
		UCanvasPanel::StaticClass(),
		TEXT("RadialMenuRoot"));
	WidgetTree->RootWidget = RootCanvas;

	WheelDisplay =
		WidgetTree->ConstructWidget<UProjectileColorWheelDisplay>(
			UProjectileColorWheelDisplay::StaticClass(),
			TEXT("WheelDisplay"));
	WheelDisplay->SetVisibility(ESlateVisibility::HitTestInvisible);

	UCanvasPanelSlot* WheelSlot =
		RootCanvas->AddChildToCanvas(WheelDisplay);
	WheelSlot->SetPosition(FVector2D::ZeroVector);
	WheelSlot->SetSize(FVector2D(
		ProjectileColorRadialMenu::WidgetSize,
		ProjectileColorRadialMenu::WidgetSize));
	WheelSlot->SetZOrder(0);

	CurrentEquippedLabel = WidgetTree->ConstructWidget<UTextBlock>(
		UTextBlock::StaticClass(),
		TEXT("CurrentEquippedLabel"));
	CurrentEquippedLabel->SetText(FText::GetEmpty());
	CurrentEquippedLabel->SetJustification(ETextJustify::Center);
	CurrentEquippedLabel->SetColorAndOpacity(
		FSlateColor(FLinearColor(0.88f, 0.91f, 0.98f)));
	CurrentEquippedLabel->SetShadowOffset(FVector2D(0.0f, 2.0f));
	CurrentEquippedLabel->SetShadowColorAndOpacity(
		FLinearColor(0.0f, 0.0f, 0.0f, 0.85f));
	FSlateFontInfo EquippedFont = CurrentEquippedLabel->GetFont();
	EquippedFont.Size = 18;
	EquippedFont.TypefaceFontName = TEXT("Bold");
	CurrentEquippedLabel->SetFont(EquippedFont);

	UCanvasPanelSlot* EquippedSlot =
		RootCanvas->AddChildToCanvas(CurrentEquippedLabel);
	EquippedSlot->SetPosition(FVector2D(130.0f, 24.0f));
	EquippedSlot->SetSize(FVector2D(420.0f, 50.0f));
	EquippedSlot->SetZOrder(4);

	CenterLabel = WidgetTree->ConstructWidget<UTextBlock>(
		UTextBlock::StaticClass(),
		TEXT("CenterLabel"));
	CenterLabel->SetText(FText::FromString(TEXT("Move toward a color")));
	CenterLabel->SetJustification(ETextJustify::Center);
	CenterLabel->SetAutoWrapText(true);
	CenterLabel->SetColorAndOpacity(FSlateColor(FLinearColor(0.9f, 0.93f, 1.0f)));
	CenterLabel->SetShadowOffset(FVector2D(0.0f, 2.0f));
	CenterLabel->SetShadowColorAndOpacity(
		FLinearColor(0.0f, 0.0f, 0.0f, 0.9f));
	FSlateFontInfo CenterFont = CenterLabel->GetFont();
	CenterFont.Size = 15;
	CenterFont.TypefaceFontName = TEXT("Bold");
	CenterLabel->SetFont(CenterFont);

	UCanvasPanelSlot* CenterSlot = RootCanvas->AddChildToCanvas(CenterLabel);
	CenterSlot->SetPosition(FVector2D(252.0f, 300.0f));
	CenterSlot->SetSize(FVector2D(176.0f, 80.0f));
	CenterSlot->SetZOrder(4);
}

void UProjectileColorRadialWidget::SetProjectileColorOptions(
	const TArray<FProjectileColorDefinition>& NewOptions,
	int32 CurrentSelection)
{
	Options = NewOptions;
	CurrentSelectionIndex = Options.IsEmpty()
		? INDEX_NONE
		: FMath::Clamp(CurrentSelection, 0, Options.Num() - 1);
	HoveredIndex = INDEX_NONE;

	if (!RootCanvas)
	{
		BuildBaseLayout();
	}

	RebuildOptions();
}

void UProjectileColorRadialWidget::RebuildOptions()
{
	if (!RootCanvas || !WidgetTree)
	{
		return;
	}

	for (UTextBlock* Label : OptionLabels)
	{
		if (Label)
		{
			Label->RemoveFromParent();
		}
	}
	OptionLabels.Reset();

	if (Options.IsEmpty())
	{
		RefreshVisuals();
		return;
	}

	const float AngleStep = 2.0f * PI / static_cast<float>(Options.Num());
	const float LabelRadius =
		FMath::Lerp(
			CenterDeadZoneRadius,
			MenuRadius,
			ProjectileColorRadialMenu::LabelRadiusRatio);
	const float LabelWidth = FMath::Clamp(
		450.0f / static_cast<float>(Options.Num()),
		82.0f,
		132.0f);
	const FVector2D LabelSize(LabelWidth, 62.0f);

	for (int32 Index = 0; Index < Options.Num(); ++Index)
	{
		const float Angle = -0.5f * PI + AngleStep * Index;
		const FVector2D Direction(FMath::Cos(Angle), FMath::Sin(Angle));
		const FVector2D CenterPosition(
			ProjectileColorRadialMenu::Center,
			ProjectileColorRadialMenu::Center);
		const FVector2D Position =
			CenterPosition + Direction * LabelRadius - LabelSize * 0.5f;

		UTextBlock* Label = WidgetTree->ConstructWidget<UTextBlock>();
		Label->SetText(Options[Index].DisplayName);
		Label->SetJustification(ETextJustify::Center);
		Label->SetAutoWrapText(true);
		Label->SetShadowOffset(FVector2D(0.0f, 2.0f));
		Label->SetShadowColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.8f));

		const float Luminance =
			0.2126f * Options[Index].Color.R +
			0.7152f * Options[Index].Color.G +
			0.0722f * Options[Index].Color.B;
		Label->SetColorAndOpacity(FSlateColor(
			Luminance > 0.68f
				? FLinearColor(0.015f, 0.018f, 0.025f)
				: FLinearColor::White));

		FSlateFontInfo LabelFont = Label->GetFont();
		LabelFont.Size = Options.Num() > 6 ? 12 : 14;
		LabelFont.TypefaceFontName = TEXT("Bold");
		Label->SetFont(LabelFont);

		UCanvasPanelSlot* OptionSlot =
			RootCanvas->AddChildToCanvas(Label);
		OptionSlot->SetPosition(Position);
		OptionSlot->SetSize(LabelSize);
		OptionSlot->SetZOrder(3);

		OptionLabels.Add(Label);
	}

	RefreshVisuals();
}

void UProjectileColorRadialWidget::NativeTick(
	const FGeometry& MyGeometry,
	float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	RefreshHoverFromCursor();
}

void UProjectileColorRadialWidget::RefreshHoverFromCursor()
{
	if (!FSlateApplication::IsInitialized() || Options.IsEmpty())
	{
		return;
	}

	const int32 NewHoveredIndex =
		FindOptionForCursor(FSlateApplication::Get().GetCursorPos());
	if (NewHoveredIndex != HoveredIndex)
	{
		HoveredIndex = NewHoveredIndex;
		RefreshVisuals();
	}
}

int32 UProjectileColorRadialWidget::FindOptionForCursor(
	const FVector2D& CursorPosition) const
{
	const FGeometry& Geometry = GetCachedGeometry();
	const FVector2D LocalCursor = Geometry.AbsoluteToLocal(CursorPosition);
	const FVector2D CenterPosition =
		Geometry.GetLocalSize() * 0.5f;
	const FVector2D FromCenter = LocalCursor - CenterPosition;

	if (FromCenter.SizeSquared() <
		FMath::Square(CenterDeadZoneRadius))
	{
		return INDEX_NONE;
	}

	const FVector2D Direction = FromCenter.GetSafeNormal();
	const float AngleStep = 2.0f * PI / static_cast<float>(Options.Num());
	float BestDotProduct = -2.0f;
	int32 BestIndex = INDEX_NONE;

	for (int32 Index = 0; Index < Options.Num(); ++Index)
	{
		const float Angle = -0.5f * PI + AngleStep * Index;
		const FVector2D OptionDirection(
			FMath::Cos(Angle),
			FMath::Sin(Angle));
		const float DotProduct = FVector2D::DotProduct(
			Direction,
			OptionDirection);
		if (DotProduct > BestDotProduct)
		{
			BestDotProduct = DotProduct;
			BestIndex = Index;
		}
	}

	return BestIndex;
}

void UProjectileColorRadialWidget::RefreshVisuals()
{
	if (WheelDisplay)
	{
		WheelDisplay->SetWheelData(
			Options,
			HoveredIndex,
			MenuRadius,
			CenterDeadZoneRadius);
	}

	for (int32 Index = 0; Index < OptionLabels.Num(); ++Index)
	{
		UTextBlock* Label = OptionLabels[Index];
		if (!Label)
		{
			continue;
		}

		const bool bHovered = Index == HoveredIndex;

		const float Luminance =
			0.2126f * Options[Index].Color.R +
			0.7152f * Options[Index].Color.G +
			0.0722f * Options[Index].Color.B;
		FLinearColor TextColor = Luminance > 0.68f
			? FLinearColor(0.015f, 0.018f, 0.025f)
			: FLinearColor::White;
		TextColor.A = bHovered ? 1.0f : 0.82f;

		Label->SetColorAndOpacity(FSlateColor(TextColor));
		Label->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
		Label->SetRenderScale(
			FVector2D(bHovered ? 1.1f : 1.0f));
	}

	if (CurrentEquippedLabel)
	{
		if (Options.IsValidIndex(CurrentSelectionIndex))
		{
			CurrentEquippedLabel->SetText(FText::Format(
				FText::FromString(TEXT("EQUIPPED  •  {0}")),
				Options[CurrentSelectionIndex].DisplayName));
			CurrentEquippedLabel->SetColorAndOpacity(
				FSlateColor(
					ProjectileColorRadialMenu::Brighten(
						Options[CurrentSelectionIndex].Color,
						1.22f)));
		}
		else
		{
			CurrentEquippedLabel->SetText(FText::GetEmpty());
		}
	}

	if (!CenterLabel)
	{
		return;
	}

	if (Options.IsValidIndex(HoveredIndex))
	{
		CenterLabel->SetText(FText::Format(
			FText::FromString(TEXT("RELEASE TO EQUIP\n{0}")),
			Options[HoveredIndex].DisplayName));
		CenterLabel->SetColorAndOpacity(
			FSlateColor(
				ProjectileColorRadialMenu::Brighten(
					Options[HoveredIndex].Color,
					1.28f)));
	}
	else if (Options.IsValidIndex(CurrentSelectionIndex))
	{
		CenterLabel->SetText(
			FText::FromString(TEXT("MOVE TOWARD A COLOR")));
		CenterLabel->SetColorAndOpacity(
			FSlateColor(FLinearColor(0.72f, 0.76f, 0.84f)));
	}
	else
	{
		CenterLabel->SetText(FText::FromString(TEXT("Move toward a color")));
		CenterLabel->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}
}

int32 UProjectileColorRadialWidget::GetHoveredIndex() const
{
	return HoveredIndex;
}
