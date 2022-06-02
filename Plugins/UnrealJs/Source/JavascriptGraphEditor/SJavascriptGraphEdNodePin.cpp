﻿#include "SJavascriptGraphEdNodePin.h"
#include "SLevelOfDetailBranchNode.h"
#include "JavascriptGraphAssetGraphSchema.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "Components/Widget.h"

void SJavascriptGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	typedef SJavascriptGraphPin ThisClassPin;

	bShowLabel = true;

	Visibility = TAttribute<EVisibility>(this, &SJavascriptGraphPin::GetPinVisiblity);

	GraphPinObj = InPin;
	check(GraphPinObj != NULL);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);

	if (GraphSchema->OnUsingDefaultPin.IsBound())
	{
		auto bDisable = GraphSchema->OnUsingDefaultPin.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
		if (bDisable)
		{
			SBorder::Construct(SBorder::FArguments()
				.BorderImage(this, &SJavascriptGraphPin::GetPinBorder)
				.BorderBackgroundColor(this, &SJavascriptGraphPin::GetPinColor)
				.OnMouseButtonDown(this, &ThisClassPin::OnPinMouseDown)
				.Cursor(this, &ThisClassPin::GetPinCursor)
			);
			return;
		}
	}

	const bool bIsInput = (GetDirection() == EGPD_Input);

	// Create the pin icon widget
	TSharedRef<SWidget> ActualPinWidget =
		SAssignNew(PinImage, SImage)
		.Image(this, &ThisClassPin::GetPinIcon)
		.IsEnabled(this, &ThisClassPin::GetIsConnectable)
		.ColorAndOpacity(this, &ThisClassPin::GetPinColor)
		.OnMouseButtonDown(this, &ThisClassPin::OnPinMouseDown)
		.Cursor(this, &ThisClassPin::GetPinCursor);
	if (GraphSchema->OnGetActualPinWidget.IsBound())
	{
		auto Widget = GraphSchema->OnGetActualPinWidget.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) }).Widget;
		if (Widget.IsValid())
		{
			ActualPinWidget = Widget.ToSharedRef();
		}
	}

	// Create the pin indicator widget (used for watched values)
	static const FName NAME_NoBorder("NoBorder");
	TSharedRef<SWidget> PinStatusIndicator =
		SNew(SButton)
		.ButtonStyle(FEditorStyle::Get(), NAME_NoBorder)
		.Visibility(this, &ThisClassPin::GetPinStatusIconVisibility)
		.ContentPadding(0)
		.OnClicked(this, &ThisClassPin::ClickedOnPinStatusIcon)
		[
			SNew(SImage)
			.Image(this, &ThisClassPin::GetPinStatusIcon)
		];
	if (GraphSchema->OnGetPinStatusIndicator.IsBound())
	{
		auto Widget = GraphSchema->OnGetPinStatusIndicator.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) }).Widget;
		if (Widget.IsValid())
		{
			PinStatusIndicator = Widget.ToSharedRef();
		}
	}

	TSharedRef<SWidget> InLabelWidget = SNew(STextBlock)
		.Text(this, &ThisClassPin::GetPinLabel)
		.TextStyle(FEditorStyle::Get(), InArgs._PinLabelStyle)
		.Visibility(this, &ThisClassPin::GetPinLabelVisibility)
		.ColorAndOpacity(this, &ThisClassPin::GetPinTextColor);
	TSharedRef<SWidget> InValueWidget = SNew(SBox);
	if (GraphSchema->OnGetValueWidget.IsBound())
	{
		auto Widget = GraphSchema->OnGetValueWidget.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) }).Widget;
		if (Widget.IsValid())
		{
			InValueWidget = Widget.ToSharedRef();
		}
	}
	// Create the widget used for the pin body (status indicator, label, and value)
	LabelAndValue = SNew(SWrapBox).PreferredWidth(150.f);

	if (bIsInput)
	{
		LabelAndValue->AddSlot()
			.VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];


		LabelAndValue->AddSlot()
			.VAlign(VAlign_Center)
			[
				InLabelWidget
			];
		LabelAndValue->AddSlot()
			.Padding(bIsInput ? FMargin(InArgs._SideToSideMargin, 0, 0, 0) : FMargin(0, 0, InArgs._SideToSideMargin, 0))
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.Padding(0.0f)
			.IsEnabled(this, &ThisClassPin::IsEditingEnabled)
			[
				InValueWidget
			]
			];
	}
	else
	{
		LabelAndValue->AddSlot()
			.VAlign(VAlign_Center)
			[
				InLabelWidget
			];

		LabelAndValue->AddSlot()
			.Padding(bIsInput ? FMargin(InArgs._SideToSideMargin, 0, 0, 0) : FMargin(0, 0, InArgs._SideToSideMargin, 0))
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.Padding(0.0f)
			.IsEnabled(this, &ThisClassPin::IsEditingEnabled)
			[
				InValueWidget
			]
			];

		LabelAndValue->AddSlot()
			.VAlign(VAlign_Center)
			[
				PinStatusIndicator
			];
	}

	TSharedPtr<SHorizontalBox> PinContent;
	if (bIsInput)
	{
		// Input pin
		FullPinHorizontalRowWidget = PinContent =
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0, 0, InArgs._SideToSideMargin, 0)
			[
				ActualPinWidget
			]
		+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				LabelAndValue.ToSharedRef()
			];
	}
	else
	{
		// Output pin
		FullPinHorizontalRowWidget = PinContent = SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				LabelAndValue.ToSharedRef()		
			]
		+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(InArgs._SideToSideMargin, 0, 0, 0)
			[
				ActualPinWidget
			];
	}

	// Set up a hover for pins that is tinted the color of the pin.
	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SJavascriptGraphPin::GetPinBorder)
		.BorderBackgroundColor(this, &SJavascriptGraphPin::GetPinColor)
		.OnMouseButtonDown(this, &ThisClassPin::OnPinNameMouseDown)
		[
			SNew(SLevelOfDetailBranchNode)
			.UseLowDetailSlot(this, &ThisClassPin::UseLowDetailPinNames)
		.LowDetail()
		[
			//@TODO: Try creating a pin-colored line replacement that doesn't measure text / call delegates but still renders
			ActualPinWidget
		]
	.HighDetail()
		[
			PinContent.ToSharedRef()
		]
		]
	);

	TAttribute<FText> ToolTipAttribute = TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SJavascriptGraphPin::GetTooltipText));
	SetToolTipText(ToolTipAttribute);
}

EVisibility SJavascriptGraphPin::GetDefaultValueVisibility() const
{
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);
	if (GraphSchema->OnGetDefaultValueVisibility.IsBound())
	{
		bool bVisibility = GraphSchema->OnGetDefaultValueVisibility.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
		return bVisibility ? EVisibility::Visible : EVisibility::Collapsed;
	}

	return SGraphPin::GetDefaultValueVisibility();
}

const FSlateBrush* SJavascriptGraphPin::GetPinBorder() const
{
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);

	if (GraphSchema->OnGetSlateBrushName.IsBound())
	{
		FName SlateBrushName = GraphSchema->OnGetSlateBrushName.Execute(IsHovered(), FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
		if (SlateBrushName.IsNone() == false)
		{
			return FEditorStyle::GetBrush(SlateBrushName);
		}
	}

	return SGraphPin::GetPinBorder();
}

FSlateColor SJavascriptGraphPin::GetPinColor() const
{
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);

	if (GraphSchema->OnGetPinColor.IsBound())
	{
		return GraphSchema->OnGetPinColor.Execute(IsHovered(), FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
	}

	return SGraphPin::GetPinColor();
}

FSlateColor SJavascriptGraphPin::GetPinTextColor() const
{
	// SGraphPin::GetPinTextColor()
	if (UEdGraphNode* GraphNode = GraphPinObj->GetOwningNodeUnchecked())
	{
		const bool bDisabled = (!GraphNode->IsNodeEnabled() || GraphNode->IsDisplayAsDisabledForced() || !IsEditingEnabled() || GraphNode->IsNodeUnrelated());
		if (GraphPinObj->bOrphanedPin)
		{
			FLinearColor PinColor = FLinearColor::Red;
			if (bDisabled)
			{
				PinColor.A = .25f;
			}
			return PinColor;
		}
		else if (bDisabled)
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);
		}
		if (bUsePinColorForText)
		{
			return GetPinColor();
		}
	}
	// else
	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);

	if (GraphSchema->OnGetPinTextColor.IsBound())
	{
		return GraphSchema->OnGetPinTextColor.Execute(IsHovered(), FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
	}

	return FLinearColor::White;
}

void SJavascriptGraphPin::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	if (OwnerNodePtr.IsValid())
	{
		SGraphPin::OnMouseLeave(MouseEvent);
	}
}

EVisibility SJavascriptGraphPin::GetPinVisiblity() const
{
	// The pin becomes too small to use at low LOD, so disable the hit test.
	if (UseLowDetailPinNames())
	{
		return EVisibility::HitTestInvisible;
	}
	return EVisibility::Visible;
}

const FSlateBrush* SJavascriptGraphPin::GetPinIcon() const
{
	if (GraphPinObj->PinType.PinCategory == TEXT("exec"))
	{
		if (IsConnected())
		{
			return IsHovered() ? FEditorStyle::GetBrush(TEXT("Graph.ExecPin.ConnectedHovered")) : FEditorStyle::GetBrush(TEXT("Graph.ExecPin.Connected"));
		}
		else
		{
			return IsHovered() ? FEditorStyle::GetBrush(TEXT("Graph.ExecPin.DisconnectedHovered")) : FEditorStyle::GetBrush(TEXT("Graph.ExecPin.Disconnected"));
		}
	}

	return SGraphPin::GetPinIcon();
}

EVisibility SJavascriptGraphPin::GetPinLabelVisibility() const
{
	if (GraphPinObj->PinType.PinCategory == TEXT("exec"))
	{
		return EVisibility::Collapsed;
	}

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	auto GraphSchema = CastChecked<UJavascriptGraphAssetGraphSchema>(Schema);
	if (GraphSchema->OnGetPinLabelVisibility.IsBound())
	{
		bool bVisible = GraphSchema->OnGetPinLabelVisibility.Execute(FJavascriptEdGraphPin{ const_cast<UEdGraphPin*>(GraphPinObj) });
		return bVisible ? EVisibility::Visible : EVisibility::Collapsed;
	}
	// 	else if (GraphPinObj->Direction == EGPD_Output)
	// 	{
	// 		return EVisibility::Collapsed;
	// 	}

	return SGraphPin::GetPinLabelVisibility();
}
