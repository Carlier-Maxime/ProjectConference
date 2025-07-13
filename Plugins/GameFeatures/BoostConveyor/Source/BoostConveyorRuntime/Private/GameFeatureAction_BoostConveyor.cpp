// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFeatureAction_BoostConveyor.h"

#include "ConveyorLogicComponent.h"

void UGameFeatureAction_BoostConveyor::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);
	OldSpeed = UConveyorLogicComponent::GetCurrentSpeed();
	UConveyorLogicComponent::SetCurrentSpeed(Speed);
}

void UGameFeatureAction_BoostConveyor::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	UConveyorLogicComponent::SetCurrentSpeed(OldSpeed);
	Super::OnGameFeatureDeactivating(Context);
}
