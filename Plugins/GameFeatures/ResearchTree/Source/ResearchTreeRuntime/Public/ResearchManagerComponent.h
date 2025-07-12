// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResearchWidget.h"
#include "Components/ActorComponent.h"
#include "ResearchManagerComponent.generated.h"


class UResearchInputConfig;
class UInputMappingContext;
class UInputAction;
class UResearchNodeData;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RESEARCHTREERUNTIME_API UResearchManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResearchManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UInputAction> OpenTreeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UResearchWidget> WidgetClass;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void StartResearch(UResearchNodeData* Node);
	UFUNCTION(BlueprintCallable)
	bool CanResearch(UResearchNodeData* Node) const;
	void OpenCloseTree();

private:
	UPROPERTY(EditAnywhere)
	TArray<UResearchNodeData*> Nodes;
	void FinishResearch(UResearchNodeData& Node);
	UPROPERTY()
	UResearchWidget* Widget = nullptr;
};
