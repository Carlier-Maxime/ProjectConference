// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResearchNodeData.h"
#include "Blueprint/UserWidget.h"
#include "ResearchWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RESEARCHTREERUNTIME_API UResearchWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UResearchNodeData* Root;
};
