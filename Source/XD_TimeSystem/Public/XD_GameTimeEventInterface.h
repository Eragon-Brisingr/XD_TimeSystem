﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XD_GameTimeEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UXD_GameTimeEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XD_TIMESYSTEM_API IXD_GameTimeEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "游戏|时间系统")
	void ConfigGameTimeEvent();
	void ConfigGameTimeEvent_Implementation(){}

	static void InvokeConfigGameTimeEvent(class AActor* Actor);
};
