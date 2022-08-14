// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "Editor/PropertyEditor/Public/IStructureDetailsView.h"

#include "TabWrapperBase.h"

// TODO(agreene): create a tab wrapper for the preview display

struct FPreviewSettingsTabWrapper : public FTabWrapperBase
{
	FPreviewSettingsTabWrapper();

	virtual void Initialize_Internal() override;
	virtual TSharedRef<SWidget> GenerateTabContent() override;

public:

	void HandleShowNeighborEdgesClicked(ECheckBoxState NewState);
	void HandleShowConnectionsClicked(ECheckBoxState NewState);
	void HandleOutlineColorLayerClicked(ECheckBoxState NewState);
	void HandleOutlineColorSectionClicked(ECheckBoxState NewState);
	void HandleOutlineColorFragmentClicked(ECheckBoxState NewState);

	FReply HandlePreviewActionButtonClicked();
};

struct FOutlineSettingsTabWrapper : public FTabWrapperBase
{
	FOutlineSettingsTabWrapper();

	virtual void Initialize_Internal() override;
	virtual TSharedRef<SWidget> GenerateTabContent() override;
};

struct FStructDetailsTabWrapper : public FTabWrapperBase
{
	FStructDetailsTabWrapper();

	/** Links this tab to a piece of data so that the user can edit it. */
	void SetData(UStruct* StructType, void* StructData, TFunction<void(const FPropertyChangedEvent&)> OnDataChanged);

	virtual void Initialize_Internal() override;
	virtual TSharedRef<SWidget> GenerateTabContent() override;

	TSharedPtr<IStructureDetailsView> DetailsView{ nullptr };
	FDelegateHandle OnDataChangedHandle;
};

// WIP
struct FMazePreviewTabWrapper : public FTabWrapperBase
{
	
};