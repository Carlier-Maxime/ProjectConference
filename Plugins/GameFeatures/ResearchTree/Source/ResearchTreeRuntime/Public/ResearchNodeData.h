// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ResearchNodeData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class RESEARCHTREERUNTIME_API UResearchNodeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName NodeID;

	UPROPERTY(EditDefaultsOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UResearchNodeData>> Prerequisites;

	UPROPERTY(EditDefaultsOnly)
	FPrimaryAssetId FeatureToActivateId = FPrimaryAssetId("GameFeatureData", NAME_None);

	UPROPERTY(EditDefaultsOnly)
	float ResearchCost;
};
