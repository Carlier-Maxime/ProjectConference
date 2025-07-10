// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResearchManagerComponent.generated.h"


class UResearchNodeData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RESEARCHTREERUNTIME_API UResearchManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResearchManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void StartResearch(UResearchNodeData* Node);
	bool CanResearch(UResearchNodeData* Node) const;

private:
	UPROPERTY(EditAnywhere)
	UResearchNodeData* root = nullptr;
	void FinishResearch(UResearchNodeData& Node);
};
