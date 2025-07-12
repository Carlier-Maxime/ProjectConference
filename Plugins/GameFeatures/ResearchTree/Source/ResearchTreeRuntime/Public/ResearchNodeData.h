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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName NodeID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UResearchNodeData>> Prerequisites;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPrimaryAssetId FeatureToActivateId = FPrimaryAssetId("GameFeatureData", NAME_None);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ResearchCost;
};
