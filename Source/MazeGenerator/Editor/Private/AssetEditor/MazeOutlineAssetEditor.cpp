// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeOutlineAssetEditor.h"

#include "Framework/Docking/TabManager.h"
#include "AssetEditorModeManager.h"
#include "MazeOutlineEdMode.h"

FMazeOutlineAssetEditor::FMazeOutlineAssetEditor()
{
	WorkspaceMenuName = TEXT("MOCEd");
}

FMazeOutlineAssetEditor::~FMazeOutlineAssetEditor()
{
	// Empty for now
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

	for (TSharedPtr<FTabWrapperBase> TabWrapper : TabCollection)
	{
		TabWrapper->TabColor = GetWorldCentricTabColorScale();
		InTabManager->RegisterTabSpawner(*TabWrapper->UniqueName, FOnSpawnTab::CreateSP(TabWrapper.Get(), &FTabWrapperBase::HandleSpawn))
			.SetDisplayName(FText::FromString(TabWrapper->DisplayName))
			.SetGroup(WorkspaceMenuCategoryRef);
	}
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
	return FName(TEXT("MazeOutlineCacheEditor"));
}

FText FMazeOutlineAssetEditor::GetToolkitName() const
{
	return FText::FromString(TEXT("Maze Outline Editor"));
}

FText FMazeOutlineAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("MOCEd"));
}

FText FMazeOutlineAssetEditor::GetToolkitToolTipText() const
{
	return FText::FromString(TEXT("Modifies a maze outline, which can be handed to the maze generator."));
}

FString FMazeOutlineAssetEditor::GetWorldCentricTabPrefix() const
{
	return FString(TEXT("MOCEd"));
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
	return FTabManager::NewLayout("Maze_Outline_Editor_v1_1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(*DefaultViewportTab->UniqueName, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.5)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.66)
					->AddTab(*PreviewSettingsTab->UniqueName, ETabState::OpenedTab)
					->AddTab(*OutlineSettingsTab->UniqueName, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.33)
					->AddTab(*LayerDetailsTab->UniqueName, ETabState::OpenedTab)
					->AddTab(*SectionDetailsTab->UniqueName, ETabState::OpenedTab)
					->AddTab(*FragmentDetailsTab->UniqueName, ETabState::OpenedTab)
				)
			)
		);
}

void FMazeOutlineAssetEditor::SetupTabs(UMazeOutlineCache* Object)
{
	DefaultViewportTab = MakeShared<FTabWrapperBase>();

	PreviewSettingsTab = MakeShared<FPreviewSettingsTabWrapper>();
	OutlineSettingsTab = MakeShared<FOutlineSettingsTabWrapper>();

	LayerDetailsTab = MakeShared<FStructDetailsTabWrapper>();
	LayerDetailsTab->DisplayName = TEXT("Layer Details");

	SectionDetailsTab = MakeShared<FStructDetailsTabWrapper>();
	SectionDetailsTab->DisplayName = TEXT("Section Details");

	FragmentDetailsTab = MakeShared<FStructDetailsTabWrapper>();
	FragmentDetailsTab->DisplayName = TEXT("Fragment Details");

	// Store all tabs in a container so other systems can know what tabs to add
	TabCollection = { 
		DefaultViewportTab, 
		PreviewSettingsTab, 
		OutlineSettingsTab, 
		LayerDetailsTab, 
		SectionDetailsTab, 
		FragmentDetailsTab 
	};

	// Ensure all tabs have unique names
	TMap<FString, TArray<TSharedPtr<FTabWrapperBase>>> TabsByName;
	for (TSharedPtr<FTabWrapperBase> Tab : TabCollection)
	{
		if (!Tab.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::SetupTabs] Null tab found in tab collection"))
			continue;
		}

		// Add numerals to unique name when repeated
		if (TabsByName.Contains(Tab->UniqueName))
		{
			Tab->UniqueName += FString::FromInt(TabsByName[Tab->UniqueName].Num());
		}
		else
		{
			TabsByName.Add(Tab->UniqueName, TArray<TSharedPtr<FTabWrapperBase>>{ Tab });
		}
	}
}

void FMazeOutlineAssetEditor::SetupEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& Host, UMazeOutlineCache* Object)
{
	CurrentCache = Object;
	Object->SetFlags(RF_Transactional);

	CreateEditorModeManager();

	FName EditorModeId = FName(TEXT("MazeOutlineCache MazeOutlineEdMode"));
	FString EditorModeText = FString(TEXT("Maze Outline Editor"));
	if (!FEditorModeRegistry::Get().GetFactoryMap().Contains(EditorModeId))
	{
		FEditorModeRegistry::Get().RegisterMode<FMazeOutlineEdMode>(EditorModeId, FText::FromString(EditorModeText), FSlateIcon(), false);
	}

	SetupTabs(Object);

	FWorkflowCentricApplication::InitAssetEditor(Mode, Host, GetToolkitFName(), GenerateInterfaceLayout(), true, true, Object);
}

void FMazeOutlineAssetEditor::HandleAssetChanged(const FPropertyChangedEvent& Event)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::HandleAssetChanged] Not implemented"));
}

void FMazeOutlineAssetEditor::ResertEditorInterfaceState()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::ResertEditorInterfaceState] Not implemented"));
}
