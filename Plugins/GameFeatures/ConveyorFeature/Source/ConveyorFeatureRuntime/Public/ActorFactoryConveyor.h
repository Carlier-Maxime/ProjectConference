// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "ActorFactoryConveyor.generated.h"

/**
 * 
 */
UCLASS()
class CONVEYORFEATURERUNTIME_API UActorFactoryConveyor : public UActorFactory
{
	GENERATED_BODY()

public:
	UActorFactoryConveyor();

protected:
	virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform,
		const FActorSpawnParameters& InSpawnParams) override;
};
