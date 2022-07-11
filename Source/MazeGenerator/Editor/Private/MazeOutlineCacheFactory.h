// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
#include "MazeOutlineCache.h"

#include "MazeOutlineCacheFactory.generated.h"

UCLASS()
class UMazeOutlineCacheFactory : public UFactory
{
	GENERATED_BODY()

public:

	UMazeOutlineCacheFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UMazeOutlineCache::StaticClass();
	}

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		UMazeOutlineCache* Output = nullptr;

		if (Class == SupportedClass && (RF_Public & Flags) != 0)
		{
			Output = NewObject<UMazeOutlineCache>(InParent, Name, Flags);
		}

		return Output;
	}

};