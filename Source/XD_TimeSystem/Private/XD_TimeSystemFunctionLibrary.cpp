// Fill out your copyright notice in the Description page of Project Settings.

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

float UXD_TimeManagerFunctionLibrary::GetGameTimeSpendRate(const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->TimeSpendRate;
	}
	return 1.f;
}

void UXD_TimeManagerFunctionLibrary::InvokeSetGameTimeSpendRate(const UObject* WorldContextObject, float Rate)
{
	if (Rate >= 0.f && Rate < 1000000.f)
	{
		if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
		{
			TimeManager->SetTimeSpendRate(Rate);
		}
	}
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

void UXD_TimeManagerFunctionLibrary::AddEveryWeekEvent_Instant(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryWeekEvent_Instant(EveryWeekConfig, EveryWeekDayEvent);
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

void UXD_TimeManagerFunctionLibrary::AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& SpecialTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddSpecialTimeEvent_Instant(SpecialTimeConfig, SpecialTimeEvent);
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

void UXD_TimeManagerFunctionLibrary::RemoveEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveEveryWeekEvent(EveryWeekConfig, EveryWeekEvent);
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

void UXD_TimeManagerFunctionLibrary::RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& SpecialTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveSpecialTimeEvent(SpecialTimeConfig, SpecialTimeEvent);
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

bool UXD_TimeManagerFunctionLibrary::ContainsEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekDayEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		return TimeManager->ContainsEveryWeekEvent(EveryWeekConfig, EveryWeekDayEvent);
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

void UXD_TimeManagerFunctionLibrary::AddEveryHourEvent_Duration(const FXD_EveryHourConfig& Start, const FXD_EveryHourConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryHourEvent_Duration(Start, End, Event);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryDayEvent_Duration(const FXD_EveryDayConfig& Start, const FXD_EveryDayConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryDayEvent_Duration(Start, End, Event);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryWeekEvent_Duration(const FXD_EveryWeekConfig& Start, const FXD_EveryWeekConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryWeekEvent_Duration(Start, End, Event);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryMonthEvent_Duration(const FXD_EveryMonthConfig& Start, const FXD_EveryMonthConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryMonthEvent_Duration(Start, End, Event);
	}
}

void UXD_TimeManagerFunctionLibrary::AddEveryYearEvent_Duration(const FXD_EveryYearConfig& Start, const FXD_EveryYearConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddEveryYearEvent_Duration(Start, End, Event);
	}
}

void UXD_TimeManagerFunctionLibrary::AddSpecialTimeEvent_Duration(const FXD_SpecialTimeConfig& Start, const FXD_SpecialTimeConfig& End, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddSpecialTimeEvent_Duration(Start, End, EveryHourEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::GameTimeDelay(const UObject* WorldContextObject, const FXD_GameTimeSpan& TimeSpan, FLatentActionInfo LatentInfo)
{
	if (TimeSpan.GetTicks() > 0)
	{
		if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
		{
			if (!TimeManager->ContainsDelayEvent(LatentInfo))
			{
				TimeManager->AddDelayEvent(TimeSpan, LatentInfo);
			}
		}
	}
	else if (LatentInfo.CallbackTarget)
	{
		if (UFunction* TargetFunction = LatentInfo.CallbackTarget->FindFunction(LatentInfo.ExecutionFunction))
		{
			LatentInfo.CallbackTarget->ProcessEvent(TargetFunction, &(LatentInfo.Linkage));
		}
	}
}

void UXD_TimeManagerFunctionLibrary::GameTimeRetriggerableDelay(const UObject* WorldContextObject, const FXD_GameTimeSpan& TimeSpan, FLatentActionInfo LatentInfo)
{
	if (TimeSpan.GetTicks() > 0)
	{
		if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
		{
			if (UXD_TimeManager::FGameTimeDelayAction* Action = TimeManager->FindDelayEvent(LatentInfo))
			{
				Action->TicksRemaining = TimeSpan.GetTicks();
			}
			else
			{
				TimeManager->AddDelayEvent(TimeSpan, LatentInfo);
			}
		}
	}
	else if (LatentInfo.CallbackTarget)
	{
		if (UFunction* TargetFunction = LatentInfo.CallbackTarget->FindFunction(LatentInfo.ExecutionFunction))
		{
			LatentInfo.CallbackTarget->ProcessEvent(TargetFunction, &(LatentInfo.Linkage));
		}
	}
}

void UXD_TimeManagerFunctionLibrary::AddRecordableDelayEvent(const FXD_GameTimeSpan& GameTimeSpan, const FXD_GameTimeEvent& GameTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddRecordableDelayEvent(GameTimeSpan, GameTimeEvent);
	}
}

void UXD_TimeManagerFunctionLibrary::AddRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->AddRecordableGameTimeEvent(SpecialTimeConfig, GameTimeEvent);
	}
}

bool UXD_TimeManagerFunctionLibrary::ContainsRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->ContainsRecordableGameTimeEvent(SpecialTimeConfig, GameTimeEvent);
	}
	return false;
}

void UXD_TimeManagerFunctionLibrary::RemoveRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent, const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = GetGameTimeManager(WorldContextObject))
	{
		TimeManager->RemoveRecordableGameTimeEvent(SpecialTimeConfig, GameTimeEvent);
	}
}

#undef LOCTEXT_NAMESPACE
