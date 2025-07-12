// Fill out your copyright notice in the Description page of Project Settings.


#include "ResearchManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ResearchNodeData.h"
#include "GameFeaturesSubsystem.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
UResearchManagerComponent::UResearchManagerComponent()
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResearchManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (!Owner) return;

	APawn* Pawn = Cast<APawn>(Owner);
	if (!Pawn) return;

	APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	if (!PC) return;

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find a Local Player with GetOwner"), *GetNameSafe(this));
		return;
	}
	
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		const auto IMC_ = IMC.LoadSynchronous();
		if (!IMC_) return;
		Subsystem->AddMappingContext(IMC_, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PC->InputComponent))
	{
		const auto OpenTreeAction_ = OpenTreeAction.LoadSynchronous();
		if (!OpenTreeAction_) return;
		EnhancedInputComponent->BindAction(OpenTreeAction_, ETriggerEvent::Started, this, &UResearchManagerComponent::OpenCloseTree);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// Called every frame
void UResearchManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResearchManagerComponent::StartResearch(UResearchNodeData* Node)
{
}

void UResearchManagerComponent::FinishResearch(UResearchNodeData& Node)
{
	if (!CanResearch(&Node)) return;
	const FString PluginName = Node.FeatureToActivateId.PrimaryAssetName.ToString();
	UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginName, {});
}

bool UResearchManagerComponent::CanResearch(UResearchNodeData* Node)
{
	if (!Node) return false;
	for (const auto& Prerequisite : Node->Prerequisites)
	{
		if (!Prerequisite || !Prerequisite->FeatureToActivateId.IsValid()) return false;
		FString PrereqPluginName = Prerequisite->FeatureToActivateId.PrimaryAssetName.ToString();
		if (!UGameFeaturesSubsystem::Get().IsGameFeaturePluginActive(PrereqPluginName)) return false;
	}
	return true;
}

void UResearchManagerComponent::OpenCloseTree()
{
	if (!WidgetClass) return;
	if (!Widget)
	{
		Widget = CreateWidget<UResearchWidget>(GetWorld(), WidgetClass);
		Widget->Root = Root;
		Widget->AddToViewport();
	} else {
		Widget->RemoveFromParent();
		Widget = nullptr;
	}
}
