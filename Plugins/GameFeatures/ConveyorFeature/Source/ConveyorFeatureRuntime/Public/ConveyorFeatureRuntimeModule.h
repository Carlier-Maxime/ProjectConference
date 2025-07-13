// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureData.h"
#include "Modules/ModuleManager.h"

class FConveyorFeatureRuntimeModule : public IModuleInterface
{
public:
	//~IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	static const UGameFeatureData* GetGameFeaturesData();
	//~End of IModuleInterface
};
