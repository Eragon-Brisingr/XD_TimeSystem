// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XD_TimeSystemType.h"
#include "XD_TimeSystemFunctionLibraryEx.generated.h"

/**
 * 
 */
UCLASS()
class XD_TIMESYSTEM_API UXD_TimeSystemFunctionLibraryEx : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	//时间-天文相关
public:
	static constexpr float LunarMonthOfDay = 29.53059f;
	static constexpr int64 TicksPreLunarMonth = LunarMonthOfDay * FXD_GameTime::TicksPerDay;
	
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject", CompactNodeTitle = "PhaseRate"))
	static float GetMoonPhaseRate(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统")
	static float GetLunarMonthOfDay() { return LunarMonthOfDay; }
};
