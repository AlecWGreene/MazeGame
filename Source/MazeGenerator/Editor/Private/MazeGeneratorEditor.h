// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FMazeGeneratorEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};