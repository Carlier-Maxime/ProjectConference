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

float UConveyorLogicComponent::Speed = 25.f;


// Called when the game starts
void UConveyorLogicComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
	CarriedItems.Add(GetWorld()->SpawnActor<AActor>(ItemClass));
	CarriedItems.Last()->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	
	AActor* Owner = GetOwner();
	FVector Start = Owner->GetActorLocation();
	DestinationLocation = Start + Owner->GetActorForwardVector() * 200.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	Params.AddIgnoredActor(CarriedItems.Last());

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, DestinationLocation, ECC_Visibility, Params))
	{
		TargetDestination = Hit.GetActor();
	}

	DrawDebugLine(GetWorld(), Start, DestinationLocation, FColor::Green, false, 5.0f, 0, 2.0f);
	ConveyorLogicComponents.Add(this);
}

void UConveyorLogicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!TargetDestination) return;
	const float Force = Speed * DeltaTime;
	for (const auto CarriedItem : CarriedItems)
	{
		MoveCarriedItem(CarriedItem, Force);
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

void UConveyorLogicComponent::MoveCarriedItem(AActor* CarriedItem, float Force)
{
	const FVector Current = CarriedItem->GetActorLocation();
	const FVector Dir = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const auto NewLoc = Current + Dir * Force;
	CarriedItem->SetActorLocation(NewLoc);
	if (FVector::DotProduct(DestinationLocation - NewLoc, Dir) <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Conveyor %s found destination: %s"),
			*GetOwner()->GetName(),
			*TargetDestination->GetName()
		);
		if (const auto NextConveyor = TargetDestination->FindComponentByClass<UConveyorLogicComponent>())
		{
			CarriedItems.Remove(CarriedItem);
			NextConveyor->CarriedItems.Add(CarriedItem);
		} else
		{
			CarriedItem->Destroy();
			CarriedItem = nullptr;
			CarriedItems.Remove(CarriedItem);
		}
	}
}

float UConveyorLogicComponent::GetCurrentSpeed()
{
	return Speed;
}

void UConveyorLogicComponent::SetCurrentSpeed(const float NewSpeed)
{
	Speed = NewSpeed;
}
