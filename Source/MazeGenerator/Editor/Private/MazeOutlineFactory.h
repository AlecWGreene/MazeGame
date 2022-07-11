// Copyright Alec Greene 2022. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
#include "MazeOutline.h"

#include "MazeOutlineFactory.generated.h"

UCLASS()
class UMazeOutlineFactory : public UFactory
{
	GENERATED_BODY()

public:

	UMazeOutlineFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UMazeOutline::StaticClass();
	}

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		UMazeOutline* Output = nullptr;

		if (Class == SupportedClass && (RF_Public & Flags) != 0)
		{
			Output = NewObject<UMazeOutline>(InParent, Name, Flags);
			Output->Fragments.Add(FMazeFragmentOutline());
		}

		return Output;
	}

};