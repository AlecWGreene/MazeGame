// Copyright Alec Greene 2022. All Rights Reserved.

#include "MazeOutlineAssetEditor.h"

#include "Framework/Docking/TabManager.h"
#include "AssetEditorModeManager.h"
#include "MazeOutlineEdMode.h"

FMazeOutlineAssetEditor::FMazeOutlineAssetEditor()
{
	WorkspaceMenuName = TEXT("MOED");
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
		InTabManager->RegisterTabSpawner(*TabWrapper->UniqueName, 
				FOnSpawnTab::CreateSP(TabWrapper.Get(), &FTabWrapperBase::HandleSpawn))
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
	return FTabManager::NewLayout("Maze_Outline_Editor_v1_3")
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
					->AddTab(*FragmentDetailsTab->UniqueName, ETabState::OpenedTab)
				)
			)
		);
}

void FMazeOutlineAssetEditor::SetupTabs(UMazeOutline* Object)
{
	DefaultViewportTab = MakeShared<FTabWrapperBase>();

	PreviewSettingsTab = MakeShared<FPreviewSettingsTabWrapper>();
	OutlineSettingsTab = MakeShared<FOutlineSettingsTabWrapper>();

	FragmentDetailsTab = MakeShared<FStructDetailsTabWrapper>();
	FragmentDetailsTab->DisplayName = TEXT("Fragment Details");

	// Store all tabs in a container so other systems can know what tabs to add
	TabCollection = { 
		DefaultViewportTab, 
		PreviewSettingsTab, 
		OutlineSettingsTab,  
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

	SetupTabs(Object);

	PreviewGraph = FMazeGraph(5,6);
	ValidateGraph();

	FWorkflowCentricApplication::InitAssetEditor(Mode, Host, GetToolkitFName(), GenerateInterfaceLayout(), true, true, Object);

	HandleAssetChanged(FPropertyChangedEvent(nullptr));
}

void FMazeOutlineAssetEditor::HandleAssetChanged(const FPropertyChangedEvent& Event)
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::HandleAssetChanged] Not implemented"));
}

void FMazeOutlineAssetEditor::ResertEditorInterfaceState()
{
	UE_LOG(LogTemp, Warning, TEXT("[FMazeOutlineAssetEditor::ResertEditorInterfaceState] Not implemented"));
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
				UE_LOG(LogTemp, Display, TEXT("\tNode: %d"), *NodeLocation.ToString());

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
