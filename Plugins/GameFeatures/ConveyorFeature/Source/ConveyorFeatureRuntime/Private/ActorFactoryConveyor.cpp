// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorFactoryConveyor.h"

#include "ConveyorFeatureRuntimeModule.h"
#include "ConveyorLogicComponent.h"
#include "GameFeatureData.h"
#include "GameFeatureAction_AddComponents.h"
#include "Engine/StaticMeshActor.h"

UActorFactoryConveyor::UActorFactoryConveyor()
{
	bShouldAutoRegister = false;
	const auto Data = FConveyorFeatureRuntimeModule::GetGameFeaturesData();
	NewActorClass = nullptr;
	if (!Data)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs() failed"), __FUNCTION__);
		NewActorClass = AStaticMeshActor::StaticClass();
		return;
	}
	for (const auto Action : Data->GetActions())
	{
		const UGameFeatureAction_AddComponents* AddComponentAction = Cast<UGameFeatureAction_AddComponents>(Action);
		if (!AddComponentAction)
			continue;

		for (const auto& Entry : AddComponentAction->ComponentList)
		{
			if (Entry.ComponentClass && Entry.ComponentClass->IsChildOf(UConveyorLogicComponent::StaticClass()))
			{
				const auto Class = Entry.ActorClass.LoadSynchronous();
				if (!Class) continue;
				NewActorClass = Class;
				break;
			}
		}
		if (NewActorClass) break;
	}
	DisplayName = NSLOCTEXT("ActorFactory", "ConveyorFactory", "Conveyor Actor Factory");
}

AActor* UActorFactoryConveyor::SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform,
	const FActorSpawnParameters& InSpawnParams)
{
	if (!NewActorClass) return nullptr;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = "A New Conveyor";
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.OverrideLevel = InLevel;

	return GetWorld()->SpawnActor<AActor>(NewActorClass, InTransform, SpawnParams);
}
