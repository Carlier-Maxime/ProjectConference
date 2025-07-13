// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"

#include "GameFeatureAction_BoostConveyor.generated.h"

/**
 * 
 */
UCLASS()
class BOOSTCONVEYORRUNTIME_API UGameFeatureAction_BoostConveyor : public UGameFeatureAction
{
	GENERATED_BODY()

public:
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	UPROPERTY(EditAnywhere, Category = "BoostConveyor")
	float Speed = 42;
private:
	float OldSpeed;
};
