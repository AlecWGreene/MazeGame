// Copyright Alec Greene 2022. All Rights Reserved.

#include "TabWrapperBase.h"
#include "EditorStyleSet.h"

FTabWrapperBase::FTabWrapperBase()
{
	UniqueName = TEXT("MOCEd_Base");
	DisplayName = TEXT("DEFAULT");
}

FTabWrapperBase::~FTabWrapperBase()
{
	RequestCloseTab();
}

TSharedRef<SDockTab> FTabWrapperBase::HandleSpawn(const FSpawnTabArgs& SpawnArgs)
{
	Initialize();

	TSharedRef<SDockTab> Tab = SNew(SDockTab)
		.Label(FText::FromString(DisplayName))
		.TabColorScale(TabColor)
		[
			GenerateTabContent()
		];
	DockTabRef = Tab;
	return Tab;
}

TSharedRef<SWidget> FTabWrapperBase::GenerateTabContent()
{
	return SNullWidget::NullWidget;
}

void FTabWrapperBase::RequestCloseTab()
{
	if (TSharedPtr<SDockTab> DockTab = DockTabRef.Pin())
	{
		DockTab->RequestCloseTab();
	}
	DockTabRef.Reset();
}

TSharedRef<SVerticalBox> FTabWrapperBase::GenerateLabelValueSplitter(const TSharedRef<SWidget>& NameHBox, const TSharedRef<SWidget>& ValueHBox)
{
	// Inspired by SDetailSingleItemRow.cpp line 640
	TSharedRef<SVerticalBox> Output = SNew(SVerticalBox)

	+ SVerticalBox::Slot()
	.VAlign(VAlign_Top)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("DetailsView.GridLine"))
		.BorderBackgroundColor_Lambda([]() -> FSlateColor { return FEditorStyle::GetSlateColor("Colors.Panel"); })
		.Padding(FMargin(0, 0, 0, 1))
		.Clipping(EWidgetClipping::ClipToBounds)
		[
			SNew(SBox)
			.MinDesiredHeight(26.0f) // TODO(agreene): Remove magic number
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("DetailsView.Highlight"))
					.BorderBackgroundColor_Lambda([]() -> FSlateColor { return FEditorStyle::GetSlateColor("Colors.Panel"); })
					[
						// Outer background
						SNew(SBorder)
						.BorderImage(FEditorStyle::GetBrush("DetailsView.CategoryMiddle"))
						.BorderBackgroundColor_Lambda([]() -> FSlateColor { return FEditorStyle::GetSlateColor("Colors.Panel"); })
						.Padding(0)
						[
							// Inner background
							SNew(SBorder)
							.BorderImage(FEditorStyle::GetBrush("DetailsView.CategoryMiddle"))
							.BorderBackgroundColor_Lambda([]() -> FSlateColor { return FEditorStyle::GetSlateColor("Colors.Panel"); })
							.Padding(FMargin(0.f,5.f,0.f,5.f))
							[
								// TODO(agreene): Add support for column resizing
								SNew(SSplitter)
								.Style(FEditorStyle::Get(), "DetailsView.Splitter")
								.PhysicalSplitterHandleSize(1.0f)
								.HitDetectionSplitterHandleSize(5.0f)
								
								// Name column
								+ SSplitter::Slot()
								.Value(0.5f)
								[
									NameHBox
								]

								// Value column
								+ SSplitter::Slot()
								.Value(0.5f)
								[
									ValueHBox
								]
							]
						]
					]
				]
			]
		]
	];

	return Output;
}

TSharedRef<SBox> FTabWrapperBase::GenerateIndent(int32 Level)
{
	return SNew(SBox).WidthOverride(Level * 16.f);
}

TSharedRef<SHorizontalBox> FTabWrapperBase::GenerateNameColumn(FString NameString)
{
	TSharedRef<SHorizontalBox> Output = SNew(SHorizontalBox)
		.Clipping(EWidgetClipping::OnDemand)

		// Indentation
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			GenerateIndent()
		]

		// Text
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString(NameString))
		];

	return Output;
}

void FTabWrapperBase::Initialize()
{
	if (!bInitialized)
	{
		Initialize_Internal();
		bInitialized = true;
	}
}

void FTabWrapperBase::Initialize_Internal()
{
	// DNI
}
