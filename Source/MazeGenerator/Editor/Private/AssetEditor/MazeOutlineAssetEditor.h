// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

#include "MazeOutline.h"
#include "TabWrapperBase.h"
#include "MazeOutlineEditorTabWrappers.h"

struct FMazeOutlineAssetEditor : public FWorkflowCentricApplication, public FSelfRegisteringEditorUndoClient
{
	//----- Constructor/Destructor -----//
public:

	FMazeOutlineAssetEditor();
	~FMazeOutlineAssetEditor();

	//----- AssetEditorTookit overrides -----//
public:

	virtual void CreateEditorModeManager() override;
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void PostRegenerateMenusAndToolbars() override;

	//----- IToolKit overrides -----//
public:

	virtual bool IsPrimaryEditor() const override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	//----- FEditorUndoClient overrides -----//
public:

	virtual void PostUndo(bool Success);
	virtual void PostRedo(bool Success);

	//----- Feature Methods -----//
public:

	TSharedRef<FTabManager::FLayout> GenerateInterfaceLayout();
	void SetupTabs(UMazeOutline* Object);
	void SetupEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& Host, UMazeOutline* Object);
	void HandleAssetChanged(const FPropertyChangedEvent& Event);
	void ResertEditorInterfaceState();

	//----- Instance Variables -----//
public:

	FString WorkspaceMenuName;

	TSharedPtr<class FMazeOutlineEdMode> EdMode;

	TWeakObjectPtr<UMazeOutline> CurrentOutline;

	TArray<TSharedPtr<FTabWrapperBase>> TabCollection;

	//----- Default Tab Wrappers -----//
public:

	TSharedPtr<FTabWrapperBase> DefaultViewportTab;
	
	TSharedPtr<FPreviewSettingsTabWrapper> PreviewSettingsTab;
	TSharedPtr<FOutlineSettingsTabWrapper> OutlineSettingsTab;
	
	TSharedPtr<FStructDetailsTabWrapper> FragmentDetailsTab;
};