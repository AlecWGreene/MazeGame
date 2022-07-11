// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Widgets/Docking/SDockTab.h"

struct FTabWrapperBase : public TSharedFromThis<FTabWrapperBase>
{
public:
	FTabWrapperBase();
	virtual ~FTabWrapperBase();

	/** Tells the wrapper to run any setup necessary before the tab is generated. */
	void Initialize();
	virtual void Initialize_Internal();

	/** Method used to generate the tab within the tab manager. */
	TSharedRef<SDockTab> HandleSpawn(const FSpawnTabArgs& SpawnArgs);

	/** Generates the tab widget. */
	virtual TSharedRef<SWidget> GenerateTabContent();

	void RequestCloseTab();

	FString UniqueName;
	FString DisplayName;
	FLinearColor TabColor;

	//----- Utility Methods -----//
protected:

	TSharedRef<SVerticalBox> GenerateLabelValueSplitter(const TSharedRef<SWidget>& NameHBox, const TSharedRef<SWidget>& ValueHBox);

	TSharedRef<SBox> GenerateIndent(int32 Level = 1);

	TSharedRef<SHorizontalBox> GenerateNameColumn(FString NameString);

protected:

	bool bInitialized{ false };
	TWeakPtr<SDockTab> DockTabRef;
};