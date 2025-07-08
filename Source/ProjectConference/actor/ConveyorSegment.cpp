// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorSegment.h"
#include "ModularGameplay/Public/Components/GameFrameworkComponentManager.h"


// Sets default values
AConveyorSegment::AConveyorSegment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConveyorSegment::BeginPlay()
{
	Super::BeginPlay();
	if (UGameFrameworkComponentManager* Manager = UGameFrameworkComponentManager::GetForActor(this))
	{
		Manager->AddReceiver(this);
	}
}

// Called every frame
void AConveyorSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

