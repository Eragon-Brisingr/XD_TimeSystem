﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemFunctionLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include "XD_TimeManager.h"


#define LOCTEXT_NAMESPACE "XD_TimeSystem"

FXD_GameTime UXD_GameTimeTypeFunctionLibrary::MakeGameTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second, int32 Millisecond)
{
	return FXD_GameTime(Year, Month, Day, Hour, Minute, Second, Millisecond);
}

void UXD_GameTimeTypeFunctionLibrary::BreakGameTime(FXD_GameTime Time, int32& Year, int32& Month, int32& Day, int32& Hour, int32& Minute, int32& Second, int32& Millisecond)
{
	UKismetMathLibrary::BreakDateTime(Time.DateTime, Year, Month, Day, Hour, Minute, Second, Millisecond);
}

FText UXD_GameTimeTypeFunctionLibrary::GameTimeToText(FXD_GameTime Time)
{
	return Time.ToText();
}

FString UXD_GameTimeTypeFunctionLibrary::GameTimeToString(FXD_GameTime Time)
{
	return Time.ToString();
}

UXD_TimeManager* UXD_TimeManagerFunctionLibrary::GetGameTimeManager(const UObject* WorldContextObject)
{
	return UXD_TimeManager::GetGameTimeManager(WorldContextObject);
}

FXD_GameTime UXD_TimeManagerFunctionLibrary::GetGameTime(const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->CurrentTime;
	}
	return {};
}

void UXD_TimeManagerFunctionLibrary::AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryHourEvent_Instant(EveryHourConfig, EveryHourEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryDayEvent_Instant(EveryDayConfig, EveryDayEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryWeekDayEvent_Instant(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryWeekDayEvent_Instant(EveryWeekDayConfig, EveryWeekDayEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryMonthEvent_Instant(EveryMonthConfig, EveryMonthEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryYearEvent_Instant(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryYearEvent_Instant(EveryYearConfig, EveryYearEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddSpecialTimeEvent_Instant(SpecialTimeConfig, EveryYearEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryHourEvent(EveryHourConfig, EveryHourEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryDayEvent(EveryDayConfig, EveryDayEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryWeekDayEvent(EveryWeekDayConfig, EveryWeekDayEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryMonthEvent(EveryMonthConfig, EveryMonthEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryYearEvent(EveryYearConfig, EveryYearEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveSpecialTimeEvent(SpecialTimeConfig, EveryYearEvent);
	}
}

bool UXD_TimeManagerFunctionLibrary::ContainsEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryHourEvent(EveryHourConfig, EveryHourEvent);
	}
	return false;
}

bool UXD_TimeManagerFunctionLibrary::ContainsEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryDayEvent(EveryDayConfig, EveryDayEvent);
	}
	return false;
}

bool UXD_TimeManagerFunctionLibrary::ContainsEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryWeekDayEvent(EveryWeekDayConfig, EveryWeekDayEvent);
	}
	return false;
}

bool UXD_TimeManagerFunctionLibrary::ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryMonthEvent(EveryMonthConfig, EveryMonthEvent);
	}
	return false;
}

bool UXD_TimeManagerFunctionLibrary::ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryYearEvent(EveryYearConfig, EveryYearEvent);
	}
	return false;
}

bool UXD_TimeManagerFunctionLibrary::ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsSpecialTimeEvent(SpecialTimeConfig, EveryYearEvent);
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
