// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XD_TimeSystemType.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FXD_GameTimeTask);

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_TimeSystemFunctionLibrary.MakeGameTime", HasNativeBreak = "XD_TimeSystemFunctionLibrary.BreakGameTime"))
struct XD_TIMESYSTEM_API FXD_GameTime
{
	GENERATED_BODY()

	friend class UXD_TimeSystemFunctionLibrary;
public:
	FXD_GameTime() = default;
	FXD_GameTime(int64 InTicks) : DateTime(InTicks) {}
	FXD_GameTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second = 0, int32 Millisecond = 0)
		:DateTime(Year, Month, Day, Hour, Minute, Second, Millisecond) {}

private:
	//使用FDateTime的实现，不使用继承否则没法SaveGame
	UPROPERTY(SaveGame)
	FDateTime DateTime;
public:
	//100ns == 1Tick
	static constexpr int64 NanosecondsPerTick = ETimespan::NanosecondsPerTick;
	static constexpr int64 TicksPerDay = ETimespan::TicksPerDay;
	static constexpr int64 TicksPerHour = ETimespan::TicksPerHour;
	static constexpr int64 TicksPerMicrosecond = ETimespan::TicksPerMicrosecond;
	static constexpr int64 TicksPerMillisecond = ETimespan::TicksPerMillisecond;
	static constexpr int64 TicksPerMinute = ETimespan::TicksPerMinute;
	static constexpr int64 TicksPerSecond = ETimespan::TicksPerSecond;
	static constexpr int64 TicksPerWeek = ETimespan::TicksPerWeek;

public:
	bool InRange(const FXD_GameTime& StartTime, const FXD_GameTime& EndTime) const;


public:
	FXD_GameTime operator+(const FTimespan& Other) const
	{
		return FXD_GameTime(DateTime.GetTicks() + Other.GetTicks());
	}

	FXD_GameTime& operator+=(const FTimespan& Other)
	{
		DateTime += Other.GetTicks();
		return *this;
	}

	FTimespan operator-(const FXD_GameTime& Other) const
	{
		return FTimespan(GetTicks() - Other.GetTicks());
	}

	FXD_GameTime operator-(const FTimespan& Other) const
	{
		return FXD_GameTime(DateTime.GetTicks() - Other.GetTicks());
	}

	FXD_GameTime& operator-=(const FTimespan& Other)
	{
		DateTime -= Other.GetTicks();
		return *this;
	}

	bool operator==(const FXD_GameTime& Other) const
	{
		return (DateTime == Other.DateTime);
	}

	bool operator!=(const FXD_GameTime& Other) const
	{
		return (DateTime != Other.DateTime);
	}

	bool operator>(const FXD_GameTime& Other) const
	{
		return (DateTime > Other.DateTime);
	}

	bool operator>=(const FXD_GameTime& Other) const
	{
		return (DateTime >= Other.DateTime);
	}

	bool operator<(const FXD_GameTime& Other) const
	{
		return (DateTime < Other.DateTime);
	}

	bool operator<=(const FXD_GameTime& Other) const
	{
		return (DateTime <= Other.DateTime);
	}

	FXD_GameTime GetDate() const
	{
		return FXD_GameTime(DateTime.GetDate().GetTicks());
	}

	void GetDate(int32& OutYear, int32& OutMonth, int32& OutDay) const
	{
		DateTime.GetDate(OutYear, OutMonth, OutDay);
	}

	int32 GetDay() const
	{
		return DateTime.GetDay();
	}

	void SetDay(int32 Day)
	{
		int32 MaxDays = DaysInMonth(GetYear(), GetMonth());
		DateTime = FDateTime(GetYear(), GetMonth(), Day < MaxDays ? Day : MaxDays, GetHour(), GetMinute(), GetSecond(), GetMillisecond());
	}

	EDayOfWeek GetDayOfWeek() const
	{
		return DateTime.GetDayOfWeek();
	}

	int32 GetDayOfYear() const
	{
		return DateTime.GetDayOfYear();
	}

	int32 GetHour() const
	{
		return DateTime.GetHour();
	}

	void SetHour(int32 Hour)
	{
		DateTime = FDateTime(GetYear(), GetMonth(), GetDay(), Hour, GetMinute(), GetSecond(), GetMillisecond());
	}

	int32 GetHour12() const
	{
		return DateTime.GetHour12();
	}

	double GetJulianDay() const
	{
		return DateTime.GetJulianDay();
	}

	double GetModifiedJulianDay() const
	{
		return DateTime.GetModifiedJulianDay();
	}

	int32 GetMillisecond() const
	{
		return DateTime.GetMillisecond();
	}

	void SetMillisecond(int32 Millisecond)
	{
		DateTime = FDateTime(GetYear(), GetMonth(), GetDay(), GetHour(), GetMinute(), GetSecond(), Millisecond);
	}

	int32 GetMinute() const
	{
		return DateTime.GetMinute();
	}

	void SetMinute(int32 Minute)
	{
		DateTime = FDateTime(GetYear(), GetMonth(), GetDay(), GetHour(), Minute, GetSecond(), GetMillisecond());
	}

	int32 GetMonth() const
	{
		return DateTime.GetMonth();
	}

	void SetMonth(int32 Month)
	{
		int32 MaxDays = DaysInMonth(GetYear(), Month);
		DateTime = FDateTime(GetYear(), Month, GetDay() < MaxDays ? GetDay() : MaxDays, GetHour(), GetMinute(), GetSecond(), GetMillisecond());
	}

	EMonthOfYear GetMonthOfYear() const
	{
		return DateTime.GetMonthOfYear();
	}

	int32 GetSecond() const
	{
		return DateTime.GetSecond();
	}

	void SetSecond(int32 Second)
	{
		DateTime = FDateTime(GetYear(), GetMonth(), GetDay(), GetHour(), GetMinute(), Second, GetMillisecond());
	}

	int64 GetTicks() const 
	{
		return DateTime.GetTicks(); 
	}

	FTimespan GetTimeOfDay() const
	{
		return DateTime.GetTimeOfDay();
	}

	int32 GetYear() const
	{
		return DateTime.GetYear();
	}

	void SetYear(int32 Year)
	{
		DateTime = FDateTime(Year, GetMonth(), GetDay(), GetHour(), GetMinute(), GetSecond(), GetMillisecond());
	}

	bool IsAfternoon() const
	{
		return DateTime.IsAfternoon();
	}

	bool IsMorning() const
	{
		return DateTime.IsMorning();
	}

	bool IsInLeapYear() const
	{
		return IsLeapYear(GetYear());
	}

	FText ToText() const;

	FString ToString() const;
public:
	static int32 DaysInMonth(int32 Year, int32 Month)
	{
		return FDateTime::DaysInMonth(Year, Month);
	}

	static int32 DaysInYear(int32 Year)
	{
		return FDateTime::DaysInYear(Year);
	}

	static bool IsLeapYear(int32 Year)
	{
		return FDateTime::IsLeapYear(Year);
	}

	static FXD_GameTime MaxValue()
	{
		return FXD_GameTime(FDateTime::MaxValue().GetTicks());
	}

	static FXD_GameTime MinValue()
	{
		return FXD_GameTime(FDateTime::MinValue().GetTicks());
	}

	friend uint32 GetTypeHash(const FXD_GameTime& GameTime)
	{
		return GetTypeHash(GameTime.DateTime);
	}
};

USTRUCT(BlueprintType)
struct XD_TIMESYSTEM_API FXD_EveryHourParam
{
	GENERATED_BODY()
public:
	FXD_EveryHourParam() = default;
	FXD_EveryHourParam(int32 Ticks)
		:Ticks(Ticks)
	{}

	FXD_EveryHourParam(int32 Monute)
		:Ticks(Monute * FXD_GameTime::TicksPerMinute)
	{}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType)
struct XD_TIMESYSTEM_API FXD_EveryDayParam
{
	GENERATED_BODY()
public:
	FXD_EveryDayParam() = default;
	FXD_EveryDayParam(int32 Ticks)
		:Ticks(Ticks)
	{}

	FXD_EveryDayParam(int32 Hour, int32 Monute)
		:Ticks(Hour * FXD_GameTime::TicksPerHour + Monute * FXD_GameTime::TicksPerMinute)
	{}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType)
struct XD_TIMESYSTEM_API FXD_EveryMonthParam
{
	GENERATED_BODY()
public:
	FXD_EveryMonthParam() = default;
	FXD_EveryMonthParam(int32 Ticks)
		:Ticks(Ticks)
	{}

	FXD_EveryMonthParam(int32 Day, int32 Hour, int32 Monute)
		:Ticks(Day * FXD_GameTime::TicksPerDay + Hour * FXD_GameTime::TicksPerHour + Monute * FXD_GameTime::TicksPerMinute)
	{}

private:
	UPROPERTY()
	int32 Ticks;
};

