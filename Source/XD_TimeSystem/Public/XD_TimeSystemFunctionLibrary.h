// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XD_TimeSystemType.h"
#include "XD_TimeSystemFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class XD_TIMESYSTEM_API UXD_GameTimeTypeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc, AdvancedDisplay = "3"))
	static FXD_GameTime MakeGameTime(int32 Year = 1000, int32 Month = 1, int32 Day = 1, int32 Hour = 0, int32 Minute = 0, int32 Second = 0, int32 Millisecond = 0);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakGameTime(FXD_GameTime Time, int32& Year, int32& Month, int32& Day, int32& Hour, int32& Minute, int32& Second, int32& Millisecond);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (CompactNodeTitle = "->", BlueprintAutocast))
	static FText GameTimeToText(FXD_GameTime Time);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (CompactNodeTitle = "->", BlueprintAutocast))
	static FString GameTimeToString(FXD_GameTime Time);

public:
	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InHourRange(const FXD_GameTime& GameTime, const FXD_EveryHourConfig& StartTime, const FXD_EveryHourConfig& EndTime)
	{
		return GameTime.InHourRange(StartTime, EndTime);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InDayRange(const FXD_GameTime& GameTime, const FXD_EveryDayConfig& StartTime, const FXD_EveryDayConfig& EndTime)
	{
		return GameTime.InDayRange(StartTime, EndTime);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InWeekRange(const FXD_GameTime& GameTime, const FXD_EveryWeekConfig& StartTime, const FXD_EveryWeekConfig& EndTime)
	{
		return GameTime.InWeekRange(StartTime, EndTime);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InMonthRange(const FXD_GameTime& GameTime, const FXD_EveryMonthConfig& StartTime, const FXD_EveryMonthConfig& EndTime)
	{
		return GameTime.InMonthRange(StartTime, EndTime);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InYearRange(const FXD_GameTime& GameTime, const FXD_EveryYearConfig& StartTime, const FXD_EveryYearConfig& EndTime)
	{
		return GameTime.InYearRange(StartTime, EndTime);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间")
	static bool InSpecialTimeRange(const FXD_GameTime& GameTime, const FXD_SpecialTimeConfig& StartTime, const FXD_SpecialTimeConfig& EndTime)
	{
		return GameTime.InSpecialTimeRange(StartTime, EndTime);
	}

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime + Timespan", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "游戏|时间")
	static FXD_GameTime Add_GameTimeTimeSpan(const FXD_GameTime& GameTime, const FTimespan& Other)
	{
		return GameTime + Other;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime - GameTime", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "游戏|时间")
	static FTimespan Subtract_GameTimeGameTime(const FXD_GameTime& A, const FXD_GameTime& B)
	{
		return A - B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime - Timespan", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "游戏|时间")
	static FXD_GameTime Subtract_GameTimeTimeSpan(const FXD_GameTime& GameTime, const FTimespan& Other)
	{
		return GameTime - Other;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (GameTime)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "游戏|时间")
	static bool EqualEqual_GameTimeGameTime(const FXD_GameTime& A, const FXD_GameTime& B)
	{
		return A == B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (GameTime)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "游戏|时间")
	static bool NotEqual_GameTimeGameTime(const FXD_GameTime& A, const FXD_GameTime& B)
	{
		return A != B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime > GameTime", CompactNodeTitle = ">", Keywords = "> greater"), Category = "游戏|时间")
	static bool Greater_GameTimeGameTime(FXD_GameTime A, FXD_GameTime B)
	{
		return A > B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime >= GameTime", CompactNodeTitle = ">=", Keywords = ">= greater"), Category = "游戏|时间")
	static bool GreaterEqual_GameTimeGameTime(FXD_GameTime A, FXD_GameTime B)
	{
		return A >= B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime < GameTime", CompactNodeTitle = "<", Keywords = "< less"), Category = "游戏|时间")
	static bool Less_GameTimeGameTime(FXD_GameTime A, FXD_GameTime B)
	{
		return A < B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime <= GameTime", CompactNodeTitle = "<=", Keywords = "<= less"), Category = "游戏|时间")
	static bool LessEqual_GameTimeGameTime(FXD_GameTime A, FXD_GameTime B)
	{
		return A <= B;
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDate"), Category = "游戏|时间")
	static FXD_GameTime GetDate(FXD_GameTime GameTime)
	{
		return GameTime.GetDate();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDay"), Category = "游戏|时间")
	static int32 GetDay(FXD_GameTime GameTime)
	{
		return GameTime.GetDay();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDayOfYear"), Category = "游戏|时间")
	static int32 GetDayOfYear(FXD_GameTime GameTime)
	{
		return GameTime.GetDayOfYear();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetHour"), Category = "游戏|时间")
	static int32 GetHour(FXD_GameTime GameTime)
	{
		return GameTime.GetHour();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetHour12"), Category = "游戏|时间")
	static int32 GetHour12(FXD_GameTime GameTime)
	{
		return GameTime.GetHour12();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMillisecond"), Category = "游戏|时间")
	static int32 GetMillisecond(FXD_GameTime GameTime)
	{
		return GameTime.GetMillisecond();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMinute"), Category = "游戏|时间")
	static int32 GetMinute(FXD_GameTime GameTime)
	{
		return GameTime.GetMinute();
	}
	
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统")
	static EXD_DayOfWeek GetDayOfWeek(FXD_GameTime GameTime)
	{
		return GameTime.GetDayOfWeek();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMonth"), Category = "游戏|时间")
	static int32 GetMonth(FXD_GameTime GameTime)
	{
		return GameTime.GetMonth();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetSecond"), Category = "游戏|时间")
	static int32 GetSecond(FXD_GameTime GameTime)
	{
		return GameTime.GetSecond();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetTimeOfDay"), Category = "游戏|时间")
	static FTimespan GetTimeOfDay(FXD_GameTime GameTime)
	{
		return GameTime.GetTimeOfDay();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetYear"), Category = "游戏|时间")
	static int32 GetYear(FXD_GameTime GameTime)
	{
		return GameTime.GetYear();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsGameTimefternoon"), Category = "游戏|时间")
	static bool IsAfternoon(FXD_GameTime GameTime)
	{
		return GameTime.IsAfternoon();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsMorning"), Category = "游戏|时间")
	static bool IsMorning(FXD_GameTime GameTime)
	{
		return GameTime.IsMorning();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsInLeapYear"), Category = "游戏|时间")
	static bool IsInLeapYear(FXD_GameTime GameTime)
	{
		return GameTime.IsInLeapYear();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "DaysInMonth"), Category = "游戏|时间")
	static int32 DaysInMonth(int32 Year, int32 Month)
	{
		return FXD_GameTime::DaysInMonth(Year, Month);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "DaysInYear"), Category = "游戏|时间")
	static int32 DaysInYear(int32 Year)
	{
		return FXD_GameTime::DaysInYear(Year);
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsLeapYear"), Category = "游戏|时间")
	static bool IsLeapYear(int32 Year)
	{
		return FXD_GameTime::IsLeapYear(Year);
	}
public:
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_EveryHourConfig MakeEveryHourConfig(int32 Minute)
	{
		return FXD_EveryHourConfig(Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakEveryHourConfig(const FXD_EveryHourConfig& EveryHourConfig, int32& Minute)
	{
		EveryHourConfig.GetConfig(Minute);
	}
	
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_EveryDayConfig MakeEveryDayConfig(int32 Hour, int32 Minute)
	{
		return FXD_EveryDayConfig(Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakEveryDayConfig(const FXD_EveryDayConfig& EveryDayConfig, int32& Hour, int32& Minute)
	{
		EveryDayConfig.GetConfig(Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_EveryWeekConfig MakeEveryWeekConfig(EXD_DayOfWeek Week, int32 Hour, int32 Minute)
	{
		return FXD_EveryWeekConfig(Week, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakEveryWeekConfig(const FXD_EveryWeekConfig& EveryWeekConfig, EXD_DayOfWeek& Week, int32& Hour, int32& Minute)
	{
		EveryWeekConfig.GetConfig(Week, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_EveryMonthConfig MakeEveryMonthConfig(int32 Day = 1, int32 Hour = 0, int32 Minute = 0)
	{
		return FXD_EveryMonthConfig(Day, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakEveryMonthConfig(const FXD_EveryMonthConfig& EveryMonthConfig, int32& Day, int32& Hour, int32& Minute)
	{
		EveryMonthConfig.GetConfig(Day, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_EveryYearConfig MakeEveryYearConfig(int32 Month = 1, int32 Day = 1, int32 Hour = 0, int32 Minute = 0)
	{
		return FXD_EveryYearConfig(Month, Day, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakEveryYearConfig(const FXD_EveryYearConfig& EveryYearConfig, int32& Month, int32& Day, int32& Hour, int32& Minute)
	{
		EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeMakeFunc))
	static FXD_SpecialTimeConfig MakeSpecialTimeConfig(int32 Year = 1000, int32 Month = 1, int32 Day = 1, int32 Hour = 0, int32 Minute = 0)
	{
		return FXD_SpecialTimeConfig(Year, Month, Day, Hour, Minute);
	}

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (NativeBreakFunc))
	static void BreakSpecialTimeConfig(const FXD_SpecialTimeConfig& SpecialTimeConfig, int32& Year, int32& Month, int32& Day, int32& Hour, int32& Minute)
	{
		SpecialTimeConfig.GetConfig(Year, Month, Day, Hour, Minute);
	}
};

UCLASS()
class XD_TIMESYSTEM_API UXD_TimeManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static class UXD_TimeManager* GetGameTimeManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static FXD_GameTime GetGameTime(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryWeekEvent_Instant(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryYearEvent_Instant(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent, const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static bool ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryHourEvent_Duration(const FXD_EveryHourConfig& Start, const FXD_EveryHourConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryDayEvent_Duration(const FXD_EveryDayConfig& Start, const FXD_EveryDayConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryWeekEvent_Duration(const FXD_EveryWeekConfig& Start, const FXD_EveryWeekConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryMonthEvent_Duration(const FXD_EveryMonthConfig& Start, const FXD_EveryMonthConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddEveryYearEvent_Duration(const FXD_EveryYearConfig& Start, const FXD_EveryYearConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统", meta = (WorldContext = "WorldContextObject"))
	static void AddSpecialTimeEvent_Duration(const FXD_SpecialTimeConfig& Start, const FXD_SpecialTimeConfig& End, const FXD_GameTimeEvent& Event, const UObject* WorldContextObject);
};
