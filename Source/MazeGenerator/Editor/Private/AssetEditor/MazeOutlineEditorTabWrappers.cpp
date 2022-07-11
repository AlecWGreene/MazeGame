// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeOutlineEditorTabWrappers.h"
#include "EditorStyleSet.h"

FPreviewSettingsTabWrapper::FPreviewSettingsTabWrapper()
{
	UniqueName = TEXT("MOCEd_PreviewSettings_Tab");
	DisplayName = TEXT("Preview Settings");
}

void FPreviewSettingsTabWrapper::Initialize_Internal()
{
	FTabWrapperBase::Initialize_Internal();
}

TSharedRef<SWidget> FPreviewSettingsTabWrapper::GenerateTabContent()
{
	// Checkbox for toggling visiblity of neighbor edges
	TSharedRef<SWidget> NeighborEdgesRow = GenerateLabelValueSplitter(
		GenerateNameColumn(TEXT("Show Neighbor Edges")),
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			GenerateIndent()
		]

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SCheckBox)
		]
	);
	
	// Checkbox for toggling visiblity of connection edges
	TSharedRef<SWidget> ConnectionsRow = GenerateLabelValueSplitter(
		GenerateNameColumn(TEXT("Show Connections")),
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			GenerateIndent()
		]

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SCheckBox)
		]
	);
	
	// Checkboxes for toggling outline colors
	TSharedRef<SWidget> OutlineColorsRow = GenerateLabelValueSplitter(
		GenerateNameColumn(TEXT("Show Outline Colors")),
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			GenerateIndent()
		]

		// Layer Checkbox
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.Padding(FMargin(5.f, 0.f, 5.f, 2.5f))
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Layer")))
			]

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged(this, &FPreviewSettingsTabWrapper::HandleOutlineColorLayerClicked)
			]
		]

		// Section Checkbox
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.Padding(FMargin(5.f, 0.f, 5.f, 2.5f))
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Section")))
			]

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged(this, &FPreviewSettingsTabWrapper::HandleOutlineColorSectionClicked)
			]
		]

		// Fragment Checkbox
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
				SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.Padding(FMargin(5.f, 0.f, 5.f, 2.5f))
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Fragment")))
			]

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged(this, &FPreviewSettingsTabWrapper::HandleOutlineColorFragmentClicked)
			]
		]
	);
	
	// Preview seed text field and generate button
	TSharedRef<SWidget> PreviewSeedRow = GenerateLabelValueSplitter(
		GenerateNameColumn(TEXT("Preview Seed")),
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			GenerateIndent()
		]

		// Preview seed text field
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		.Padding(FMargin(0,0,16.f,0))
		[
			SNew(SEditableTextBox)
			.Text(FText::FromString(TEXT("SeedTextHere")))
		]

		// Preview action button
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Left)
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Generate Preview")))
			.OnClicked(this, &FPreviewSettingsTabWrapper::HandlePreviewActionButtonClicked)
		]
	);

	// Combine rows into the dock tab body
	TSharedRef<SVerticalBox> TabContainer = SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()[NeighborEdgesRow]
		+ SVerticalBox::Slot().AutoHeight()[ConnectionsRow]
		+ SVerticalBox::Slot().AutoHeight()[OutlineColorsRow]
		+ SVerticalBox::Slot().AutoHeight()[PreviewSeedRow];

	return TabContainer;
}

void FPreviewSettingsTabWrapper::HandleShowNeighborEdgesClicked(ECheckBoxState NewState)
{
}

void FPreviewSettingsTabWrapper::HandleShowConnectionsClicked(ECheckBoxState NewState)
{
}

void FPreviewSettingsTabWrapper::HandleOutlineColorLayerClicked(ECheckBoxState NewState)
{
}

void FPreviewSettingsTabWrapper::HandleOutlineColorSectionClicked(ECheckBoxState NewState)
{
}

void FPreviewSettingsTabWrapper::HandleOutlineColorFragmentClicked(ECheckBoxState NewState)
{

}

FReply FPreviewSettingsTabWrapper::HandlePreviewActionButtonClicked()
{
	return FReply::Handled();
}

FOutlineSettingsTabWrapper::FOutlineSettingsTabWrapper()
{
	UniqueName = TEXT("MOCEd_OutlineSettings_Tab");
	DisplayName = TEXT("Outline Settings");
}

void FOutlineSettingsTabWrapper::Initialize_Internal()
{
	FTabWrapperBase::Initialize_Internal();
}

TSharedRef<SWidget> FOutlineSettingsTabWrapper::GenerateTabContent()
{
	return SNullWidget::NullWidget;
}

FStructDetailsTabWrapper::FStructDetailsTabWrapper()
{
	UniqueName = TEXT("MOCEd_StructDetails_Tab");
	DisplayName = TEXT("Struct Details");
}

void FStructDetailsTabWrapper::Initialize_Internal()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditorModule");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bShowAnimatedPropertiesOption = false;
	DetailsViewArgs.bShowKeyablePropertiesOption = false;

	FStructureDetailsViewArgs StructureViewArgs;

	DetailsView = PropertyEditorModule.CreateStructureDetailView(DetailsViewArgs, StructureViewArgs, nullptr);
}

TSharedRef<SWidget> FStructDetailsTabWrapper::GenerateTabContent()
{
	return DetailsView.IsValid() ? DetailsView->GetWidget().ToSharedRef() : SNullWidget::NullWidget;
}