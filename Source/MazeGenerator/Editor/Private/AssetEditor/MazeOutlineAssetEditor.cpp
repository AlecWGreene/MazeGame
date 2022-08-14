// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeOutlineAssetEditor.h"

#include "Framework/Docking/TabManager.h"
#include "AssetEditorModeManager.h"
#include "MazeOutlineEdMode.h"
#include "SAssetEditorViewport.h"
#include "AssetEditorViewportLayout.h"
#include "IStructureDetailsView.h"

struct FMazeOutlineAssetEditorTabs
{
	static inline FName ViewportTabName = "DefaultViewportTab";
	static inline FName PreviewSettingsTabName = "PreviewSettingsTab";
	static inline FName OutlineSettingsTabName = "OutlineSettingsTab";
	static inline FName FragmentSettingsTabName = "FragmentSettingsTab";
};

FMazeOutlineAssetEditor::FMazeOutlineAssetEditor()
{
	WorkspaceMenuName = TEXT("MOED");
}

FMazeOutlineAssetEditor::~FMazeOutlineAssetEditor()
{
	FWorkflowCentricApplication::~FWorkflowCentricApplication();
}

void FMazeOutlineAssetEditor::CreateEditorModeManager()
{
	if (!EditorModeManager)
	{
		EditorModeManager = MakeShareable(new FAssetEditorModeManager());
	}
}

void FMazeOutlineAssetEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(FText::FromString(WorkspaceMenuName));
	TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FMazeOutlineAssetEditorTabs::ViewportTabName,
			FOnSpawnTab::CreateSP(this, &FMazeOutlineAssetEditor::SpawnTab_Viewport))
		.SetDisplayName(FText::FromString(TEXT("Preview")))
		.SetGroup(WorkspaceMenuCategoryRef);

	InTabManager->RegisterTabSpawner(FMazeOutlineAssetEditorTabs::PreviewSettingsTabName,
			FOnSpawnTab::CreateSP(this, &FMazeOutlineAssetEditor::SpawnTab_PreviewSettings))
		.SetDisplayName(FText::FromString(TEXT("Preview Settings")))
		.SetGroup(WorkspaceMenuCategoryRef);

	InTabManager->RegisterTabSpawner(FMazeOutlineAssetEditorTabs::OutlineSettingsTabName,
			FOnSpawnTab::CreateSP(this, &FMazeOutlineAssetEditor::SpawnTab_OutlineSettings))
		.SetDisplayName(FText::FromString(TEXT("Outline Settings")))
		.SetGroup(WorkspaceMenuCategoryRef);

	InTabManager->RegisterTabSpawner(FMazeOutlineAssetEditorTabs::FragmentSettingsTabName,
			FOnSpawnTab::CreateSP(this, &FMazeOutlineAssetEditor::SpawnTab_FragmentSettings))
		.SetDisplayName(FText::FromString(TEXT("Fragment Settings")))
		.SetGroup(WorkspaceMenuCategoryRef);
}

void FMazeOutlineAssetEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(FMazeOutlineAssetEditorTabs::ViewportTabName);
	InTabManager->UnregisterTabSpawner(FMazeOutlineAssetEditorTabs::PreviewSettingsTabName);
	InTabManager->UnregisterTabSpawner(FMazeOutlineAssetEditorTabs::OutlineSettingsTabName);
	InTabManager->UnregisterTabSpawner(FMazeOutlineAssetEditorTabs::FragmentSettingsTabName);
}

void FMazeOutlineAssetEditor::PostRegenerateMenusAndToolbars()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::CreateEditorModeManager] Not implemented"));
}

bool FMazeOutlineAssetEditor::IsPrimaryEditor() const
{
	return true;
}

FName FMazeOutlineAssetEditor::GetToolkitFName() const
{
	return FName(TEXT("MazeOutlineEditor"));
}

FText FMazeOutlineAssetEditor::GetToolkitName() const
{
	return FText::FromString(TEXT("Maze Outline Editor"));
}

FText FMazeOutlineAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("MOED"));
}

FText FMazeOutlineAssetEditor::GetToolkitToolTipText() const
{
	return FText::FromString(TEXT("Modifies a maze outline, which can be handed to the maze generator."));
}

FString FMazeOutlineAssetEditor::GetWorldCentricTabPrefix() const
{
	return FString(TEXT("MOED"));
}

FLinearColor FMazeOutlineAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor();
}

void FMazeOutlineAssetEditor::PostUndo(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::PostUndo] Not implemented"));
}

void FMazeOutlineAssetEditor::PostRedo(bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::PostRedo] Not implemented"));
}

TSharedRef<FTabManager::FLayout> FMazeOutlineAssetEditor::GenerateInterfaceLayout()
{
	return FTabManager::NewLayout("Maze_Outline_Editor_v2_2")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(TEXT("DefaultViewportTab"), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.5)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.66)
					->AddTab(TEXT("PreviewSettingsTab"), ETabState::OpenedTab)
					->AddTab(TEXT("OutlineSettingsTab"), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.33)
					->AddTab(TEXT("FragmentSettingsTab"), ETabState::OpenedTab)
				)
			)
		);
}

void FMazeOutlineAssetEditor::SetupEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& Host, UMazeOutline* Object)
{
	if (!Object)
	{
		UE_LOG(LogTemp, Error, TEXT("[FMazeOutlineAssetEditor::SetupEditor] Object was null"));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("[FMazeOutlineAssetEditor::SetupEditor] %s"), *Object->GetFName().ToString());

	CurrentOutline = Object;
	Object->SetFlags(RF_Transactional);

	CreateEditorModeManager();

	FName EditorModeId = FName(TEXT("MazeOutline MazeOutlineEdMode"));
	FString EditorModeText = FString(TEXT("Maze Outline Editor"));
	if (!FEditorModeRegistry::Get().GetFactoryMap().Contains(EditorModeId))
	{
		FEditorModeRegistry::Get().RegisterMode<FMazeOutlineEdMode>(EditorModeId, FText::FromString(EditorModeText), FSlateIcon(), false);
	}

	GetEditorModeManager().ActivateMode(EditorModeId, true);

	EdMode = MakeShareable(GetEditorModeManager().GetActiveModeTyped<FMazeOutlineEdMode>(EditorModeId));
	EdMode->Editor = SharedThis(this);

	PreviewGraph = FMazeGraph(5,6);
	ValidateGraph();

	FWorkflowCentricApplication::InitAssetEditor(Mode, Host, GetToolkitFName(), GenerateInterfaceLayout(), true, true, Object);

	// Initialize tabs

	PreviewSettingsDetailsView->SetStructureData(MakeShareable(new FStructOnScope(FMazeOutlinePreviewSettings::StaticStruct(), (uint8*)&CurrentOutline->PreviewSettings)));
	OutlineSettingsDetailsView->SetStructureData(MakeShareable(new FStructOnScope(UMazeOutline::StaticClass(), (uint8*)&CurrentOutline)));

	HandleAssetChanged(FPropertyChangedEvent(nullptr));
}

void FMazeOutlineAssetEditor::HandleAssetChanged(const FPropertyChangedEvent& Event)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::HandleAssetChanged] Not implemented"));
}

void FMazeOutlineAssetEditor::HandlePreviewSettingChanged(const FPropertyChangedEvent& Event)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::HandleAssetChanged] Not implemented"));
}

void FMazeOutlineAssetEditor::ResertEditorInterfaceState()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::ResertEditorInterfaceState] Not implemented"));
}

TSharedRef<SDockTab> FMazeOutlineAssetEditor::SpawnTab_Viewport(const FSpawnTabArgs& InArgs)
{
	TSharedRef<SDockTab> Output = SNew(SDockTab)
		.Label(FText::FromString(TEXT("Preview Viewport")))
		.TabColorScale(GetWorldCentricTabColorScale());

	AssetEditorViewportFactoryFunction ViewportFactoryFunction = [&](const FAssetEditorViewportConstructionArgs& ViewportArgs) -> TSharedRef<SAssetEditorViewport>
	{
		return SNew(SAssetEditorViewport, ViewportArgs);
	};

	PreviewTabContent = MakeShareable(new FEditorViewportTabContent());
	PreviewTabContent->Initialize(ViewportFactoryFunction, Output, TEXT("MOED_PreviewViewport"));

	return Output;
}

TSharedRef<SDockTab> FMazeOutlineAssetEditor::SpawnTab_PreviewSettings(const FSpawnTabArgs& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bShowAnimatedPropertiesOption = false;
	DetailsViewArgs.bShowKeyablePropertiesOption = false;

	FStructureDetailsViewArgs StructureViewArgs;

	PreviewSettingsDetailsView = PropertyEditorModule.CreateStructureDetailView(DetailsViewArgs, StructureViewArgs, nullptr);
	PreviewSettingsDetailsView->GetOnFinishedChangingPropertiesDelegate().AddLambda([&](const FPropertyChangedEvent& Event)
		{
			UE_LOG(LogTemp, Display, TEXT("Preview setting %s changed"), *Event.GetPropertyName().ToString());
		});

	return SNew(SDockTab)
		.Label(FText::FromString(TEXT("Preview Settings")))
		.TabColorScale(GetWorldCentricTabColorScale())
		[
			PreviewSettingsDetailsView->GetWidget().ToSharedRef()
		];;
}

TSharedRef<SDockTab> FMazeOutlineAssetEditor::SpawnTab_OutlineSettings(const FSpawnTabArgs& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bShowAnimatedPropertiesOption = false;
	DetailsViewArgs.bShowKeyablePropertiesOption = false;

	FStructureDetailsViewArgs StructureViewArgs;

	OutlineSettingsDetailsView = PropertyEditorModule.CreateStructureDetailView(DetailsViewArgs, StructureViewArgs, nullptr);
	PreviewSettingsDetailsView->GetOnFinishedChangingPropertiesDelegate().AddLambda([&](const FPropertyChangedEvent& Event)
		{
			UE_LOG(LogTemp, Display, TEXT("Outline setting %s changed"), *Event.GetPropertyName().ToString());
		});

	return SNew(SDockTab)
		.Label(FText::FromString(TEXT("Outline Settings")))
		.TabColorScale(GetWorldCentricTabColorScale())
		[
			OutlineSettingsDetailsView->GetWidget().ToSharedRef()
		];
}

TSharedRef<SDockTab> FMazeOutlineAssetEditor::SpawnTab_FragmentSettings(const FSpawnTabArgs& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bShowAnimatedPropertiesOption = false;
	DetailsViewArgs.bShowKeyablePropertiesOption = false;

	FStructureDetailsViewArgs StructureViewArgs;

	FragmentSettingsDetailsView = PropertyEditorModule.CreateStructureDetailView(DetailsViewArgs, StructureViewArgs, nullptr);

	return SNew(SDockTab)
		.Label(FText::FromString(TEXT("Fragment Settings")))
		.TabColorScale(GetWorldCentricTabColorScale())
		[
			FragmentSettingsDetailsView->GetWidget().ToSharedRef()
		];
}

bool FMazeOutlineAssetEditor::ValidateGraph()
{
	bool bOutput = true;

	UE_LOG(LogTemp, Display, TEXT("=============== FMazeOutlineAssetEditor::ValidateGraph ==============="));
	for (int32 RingIndex = 0; RingIndex <= PreviewGraph.GetNumRings(); ++RingIndex)
	{
		if (RingIndex == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("\tOrigin Neighbors"));
			for (const FMazeLocation& Location : PreviewGraph.GetNodeNeighbors(FMazeLocation(0, 0)))
			{
				UE_LOG(LogTemp, Display, TEXT("\t%s"), *Location.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Ring %d"), RingIndex);

			for (int32 PositionIndex = 0; PositionIndex < RingIndex * PreviewGraph.GetNumSides(); ++PositionIndex)
			{
				FMazeLocation NodeLocation(RingIndex, PositionIndex);
				UE_LOG(LogTemp, Display, TEXT("\tNode: %s"), *NodeLocation.ToString());

				FString NeighborString = FString::Printf(TEXT("\t\tNeighbors: "));
				NeighborString += FString::JoinBy(
					PreviewGraph.GetNodeNeighbors(NodeLocation),
					TEXT(","),
					[](FMazeLocation InLocation)
					{
						return InLocation.ToString();
					}
				);

				UE_LOG(LogTemp, Display, TEXT("%s"), *NeighborString);
			}
		}
	}

	return bOutput;
}
