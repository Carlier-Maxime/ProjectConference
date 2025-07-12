// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstanceSubsystem.h"

#include "GameFeaturesSubsystem.h"
#include "GameFeaturePluginOperationResult.h"

void UMyGameInstanceSubsystem::ActivateGameFeatureByName(const FString& PluginName, bool ReActivate)
{
	FString URL;
	if (!UGameFeaturesSubsystem::Get().GetPluginURLByName(PluginName, URL))
	{
		UE_LOG(LogTemp, Warning, TEXT("Plugin '%s' non trouvé parmi les plugins disponibles."), *PluginName);
	}

	if (ReActivate)
	{
		if (UGameFeaturesSubsystem::Get().IsGameFeaturePluginActive(URL))
		{
			UGameFeaturesSubsystem::Get().DeactivateGameFeaturePlugin(URL);
		}

	}
	UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(
		URL,
		FGameFeaturePluginLoadComplete::CreateStatic(&UMyGameInstanceSubsystem::OnPluginActivated)
	);
}

void UMyGameInstanceSubsystem::OnPluginActivated(const UE::GameFeatures::FResult& Result)
{
	if (Result.HasError())
	{
		UE_LOG(LogTemp, Error, TEXT("❌ Échec activation plugin : %s"), *Result.GetError());	
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("✅ Plugin activé avec succès !"));
	}
}