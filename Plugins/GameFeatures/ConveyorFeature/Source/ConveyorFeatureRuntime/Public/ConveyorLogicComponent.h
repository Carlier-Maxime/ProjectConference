// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConveyorLogicComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CONVEYORFEATURERUNTIME_API UConveyorLogicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UConveyorLogicComponent();
	virtual ~UConveyorLogicComponent() override;
	
	
	UPROPERTY(EditAnywhere, Category = "Conveyor")
	TSubclassOf<AActor> ItemClass;
	
	UPROPERTY(EditAnywhere)
	AActor* TargetDestination;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	[[nodiscard]] FVector GetDestinationLocation() const;
	[[nodiscard]] static TArray<UConveyorLogicComponent*> GetConveyorLogicComponents();
	[[nodiscard]] static float GetCurrentSpeed();
	static void SetCurrentSpeed(float NewSpeed);

private:
	UPROPERTY()
	TArray<AActor*> CarriedItems;
	FVector DestinationLocation;
	static TArray<UConveyorLogicComponent*> ConveyorLogicComponents;
	void MoveCarriedItem(AActor* CarriedItem, float Force);
	static float Speed;
};
