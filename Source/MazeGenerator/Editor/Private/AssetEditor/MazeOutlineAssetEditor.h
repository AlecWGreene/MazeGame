// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "EditorViewportTabContent.h"

#include "MazeOutline.h"
#include "TabWrapperBase.h"
#include "MazeOutlineEditorTabWrappers.h"

#include "MazeGraph.h"

struct FMazeOutlineAssetEditor : public FWorkflowCentricApplication, public FSelfRegisteringEditorUndoClient
{
	//----- Constructor/Destructor -----//
public:

	FMazeOutlineAssetEditor();
	virtual ~FMazeOutlineAssetEditor();

	//----- AssetEditorTookit overrides -----//
public:

	virtual void CreateEditorModeManager() override;
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
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
	void SetupEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& Host, UMazeOutline* Object);
	void HandleAssetChanged(const FPropertyChangedEvent& Event);
	void HandlePreviewSettingChanged(const FPropertyChangedEvent& Event);
	void ResertEditorInterfaceState();

	//----- Tab Spawners -----//
public:

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> SpawnTab_OutlineSettings(const FSpawnTabArgs& InArgs);
	TSharedRef<SDockTab> SpawnTab_FragmentSettings(const FSpawnTabArgs& InArgs);

	//----- Utility Methods -----//
public:

	bool ValidateGraph();

	//----- Instance Variables -----//
public:

	FString WorkspaceMenuName;

	TSharedPtr<class FMazeOutlineEdMode> EdMode;

	TWeakObjectPtr<UMazeOutline> CurrentOutline;

	FMazeGraph PreviewGraph;

	TSharedPtr<class FEditorViewportTabContent> PreviewTabContent;

	TSharedPtr<class IStructureDetailsView> PreviewSettingsDetailsView{ nullptr };
	TSharedPtr<class IStructureDetailsView> OutlineSettingsDetailsView{ nullptr };
	TSharedPtr<class IStructureDetailsView> FragmentSettingsDetailsView{ nullptr };
};