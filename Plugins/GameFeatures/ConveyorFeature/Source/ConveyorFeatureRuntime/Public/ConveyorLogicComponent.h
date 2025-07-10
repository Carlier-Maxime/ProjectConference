// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConveyorLogicComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UConveyorLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UConveyorLogicComponent();
	virtual ~UConveyorLogicComponent() override;

	
	UPROPERTY(EditAnywhere, Category = "Conveyor")
	TSubclassOf<AActor> ItemClass;
	
	UPROPERTY(EditAnywhere)
	AActor* TargetDestination;

	UPROPERTY(EditAnywhere)
	float Speed = 25.f;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	AActor* CarriedItem = nullptr;
	FVector DestinationLocation;
};
