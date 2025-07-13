// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ConveyorCheatExtension.generated.h"

/**
 * 
 */
UCLASS()
class CONVEYORFEATURERUNTIME_API UConveyorCheatExtension : public UCheatManagerExtension
{
	GENERATED_BODY()
public:
	UFUNCTION(exec)
	void ShowConveyorLine() const;
};
