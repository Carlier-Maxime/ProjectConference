// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MyGameInstanceSubsystem.generated.h"

namespace UE::GameFeatures
{
	struct FResult;
}

/**
 * 
 */
UCLASS()
class PROJECTCONFERENCE_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void ActivateGameFeatureByName(const FString& PluginName, bool ReActivate = false);
	static void OnPluginActivated(const UE::GameFeatures::FResult& Result);
};
