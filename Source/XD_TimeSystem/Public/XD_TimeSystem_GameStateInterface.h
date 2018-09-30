// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XD_TimeSystem_GameStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXD_TimeSystem_GameStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XD_TIMESYSTEM_API IXD_TimeSystem_GameStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "游戏|时间系统")
	class UXD_TimeManager* GetGameTimeManager() const;
	virtual class UXD_TimeManager* GetGameTimeManager_Implementation() const { return nullptr; }
};
