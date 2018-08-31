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
class XD_TIMESYSTEM_API UXD_TimeSystemFunctionLibrary : public UBlueprintFunctionLibrary
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
	static FXD_GameTime GetDate(FXD_GameTime A)
	{
		return A.GetDate();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDay"), Category = "游戏|时间")
	static int32 GetDay(FXD_GameTime A)
	{
		return A.GetDay();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDayOfYear"), Category = "游戏|时间")
	static int32 GetDayOfYear(FXD_GameTime A)
	{
		return A.GetDayOfYear();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetHour"), Category = "游戏|时间")
	static int32 GetHour(FXD_GameTime A)
	{
		return A.GetHour();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetHour12"), Category = "游戏|时间")
	static int32 GetHour12(FXD_GameTime A)
	{
		return A.GetHour12();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMillisecond"), Category = "游戏|时间")
	static int32 GetMillisecond(FXD_GameTime A)
	{
		return A.GetMillisecond();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMinute"), Category = "游戏|时间")
	static int32 GetMinute(FXD_GameTime A)
	{
		return A.GetMinute();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMonth"), Category = "游戏|时间")
	static int32 GetMonth(FXD_GameTime A)
	{
		return A.GetMonth();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetSecond"), Category = "游戏|时间")
	static int32 GetSecond(FXD_GameTime A)
	{
		return A.GetSecond();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetTimeOfDay"), Category = "游戏|时间")
	static FTimespan GetTimeOfDay(FXD_GameTime A)
	{
		return A.GetTimeOfDay();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetYear"), Category = "游戏|时间")
	static int32 GetYear(FXD_GameTime A)
	{
		return A.GetYear();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsAfternoon"), Category = "游戏|时间")
	static bool IsAfternoon(FXD_GameTime A)
	{
		return A.IsAfternoon();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsMorning"), Category = "游戏|时间")
	static bool IsMorning(FXD_GameTime A)
	{
		return A.IsMorning();
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "IsInLeapYear"), Category = "游戏|时间")
	static bool IsInLeapYear(FXD_GameTime A)
	{
		return A.IsInLeapYear();
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
};
