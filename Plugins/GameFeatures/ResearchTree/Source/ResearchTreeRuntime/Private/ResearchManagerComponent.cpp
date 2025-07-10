// Fill out your copyright notice in the Description page of Project Settings.


#include "ResearchManagerComponent.h"

#include "ResearchNodeData.h"
#include "GameFeaturesSubsystem.h"


// Sets default values for this component's properties
UResearchManagerComponent::UResearchManagerComponent()
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResearchManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UResearchManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResearchManagerComponent::StartResearch(UResearchNodeData* Node)
{
}

void UResearchManagerComponent::FinishResearch(UResearchNodeData& Node)
{
	if (!CanResearch(&Node)) return;
	const FString PluginName = Node.FeatureToActivateId.PrimaryAssetName.ToString();
	UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginName, {});
}

bool UResearchManagerComponent::CanResearch(UResearchNodeData* Node) const
{
	if (!Node) return false;
	for (const auto& Prerequisite : Node->Prerequisites)
	{
		if (!Prerequisite || !Prerequisite->FeatureToActivateId.IsValid()) return false;
		FString PrereqPluginName = Prerequisite->FeatureToActivateId.PrimaryAssetName.ToString();
		if (!UGameFeaturesSubsystem::Get().IsGameFeaturePluginActive(PrereqPluginName)) return false;
	}
	return true;
}
