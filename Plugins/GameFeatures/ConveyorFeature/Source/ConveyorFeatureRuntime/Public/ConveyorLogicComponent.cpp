// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorLogicComponent.h"

TArray<UConveyorLogicComponent*> UConveyorLogicComponent::ConveyorLogicComponents;

// Sets default values for this component's properties
UConveyorLogicComponent::UConveyorLogicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UConveyorLogicComponent::~UConveyorLogicComponent()
{
}


// Called when the game starts
void UConveyorLogicComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
	CarriedItem = GetWorld()->SpawnActor<AActor>(ItemClass);
	CarriedItem->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	
	AActor* Owner = GetOwner();
	FVector Start = Owner->GetActorLocation();
	DestinationLocation = Start + Owner->GetActorForwardVector() * 200.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	Params.AddIgnoredActor(CarriedItem);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, DestinationLocation, ECC_Visibility, Params))
	{
		TargetDestination = Hit.GetActor();
	}

	DrawDebugLine(GetWorld(), Start, DestinationLocation, FColor::Green, false, 5.0f, 0, 2.0f);
	ConveyorLogicComponents.Add(this);
}

void UConveyorLogicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!CarriedItem || !TargetDestination) return;

	FVector Current = CarriedItem->GetActorLocation();
	FVector Dir = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float force = Speed * DeltaTime;

	CarriedItem->SetActorLocation(Current + Dir * force);
	
	if (FVector::Dist(Current, DestinationLocation) < force)
	{
		UE_LOG(LogTemp, Log, TEXT("Conveyor %s found destination: %s"),
			*GetOwner()->GetName(),
			*TargetDestination->GetName()
		);
		CarriedItem->Destroy();
		CarriedItem = nullptr;
	}
}

FVector UConveyorLogicComponent::GetDestinationLocation() const
{
	return DestinationLocation;
}

void UConveyorLogicComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ConveyorLogicComponents.Remove(this);
	Super::EndPlay(EndPlayReason);
}

TArray<UConveyorLogicComponent*> UConveyorLogicComponent::GetConveyorLogicComponents()
{
	return ConveyorLogicComponents;
}
