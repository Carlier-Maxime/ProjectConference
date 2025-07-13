// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConveyorFeatureRuntimeModule.h"

#include "GameFeaturesSubsystem.h"

#define LOCTEXT_NAMESPACE "FConveyorFeatureRuntimeModule"

void FConveyorFeatureRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory;
	// the exact timing is specified in the .uplugin file per-module
}

void FConveyorFeatureRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
	// For modules that support dynamic reloading, we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FConveyorFeatureRuntimeModule, ConveyorFeatureRuntime)

const UGameFeatureData* FConveyorFeatureRuntimeModule::GetGameFeaturesData()
{
	const FString PluginName = TEXT("ConveyorFeature");
	auto& Subsystem = UGameFeaturesSubsystem::Get();
	FString PluginURL;
	Subsystem.GetPluginURLByName(PluginName, PluginURL);
	auto Data = Subsystem.GetGameFeatureDataForActivePluginByURL(PluginURL);
	if (!Data)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameFeaturesData introuvable pour %s"), *PluginName);
		return nullptr;
	}
	return Data;
}
