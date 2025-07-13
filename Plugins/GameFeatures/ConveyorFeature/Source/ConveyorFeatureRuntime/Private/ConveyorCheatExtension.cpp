// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorCheatExtension.h"

#include "ConveyorLogicComponent.h"
#include "DrawDebugHelpers.h"

void UConveyorCheatExtension::ShowConveyorLine() const
{
	for (const auto Component : UConveyorLogicComponent::GetConveyorLogicComponents())
	{
		const auto Owner = Component->GetOwner();
		if (!Owner) return;
		auto Start = Owner->GetActorLocation();
		auto End = Component->GetDestinationLocation();
		auto Box = Owner->GetComponentsBoundingBox();
		const auto Size = Box.GetSize();
		DrawDebugLine(GetWorld(), Start + Size.Z / 1.99, End + Size.Z / 1.99, FColor::Red, true);
	}
	UE_LOG(LogTemp, Display, TEXT("ConveyorLine has been displayed with line"));
}
