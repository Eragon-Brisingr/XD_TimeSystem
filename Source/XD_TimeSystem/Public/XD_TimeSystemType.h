// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XD_TimeSystemType.generated.h"

struct FXD_EveryHourConfig;
struct FXD_EveryDayConfig;
struct FXD_EveryWeekConfig;
struct FXD_EveryMonthConfig;
struct FXD_EveryYearConfig;
struct FXD_SpecialTimeConfig;

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FXD_GameTimeEvent);

UENUM(BlueprintType)
enum class EXD_DayOfWeek : uint8
{
	Monday = 0 UMETA(DisplayName = "周一"),
	Tuesday UMETA(DisplayName = "周二"),
	Wednesday UMETA(DisplayName = "周三"),
	Thursday UMETA(DisplayName = "周四"),
	Friday UMETA(DisplayName = "周五"),
	Saturday UMETA(DisplayName = "周六"),
	Sunday UMETA(DisplayName = "周日")
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeGameTime", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakGameTime"))
struct XD_TIMESYSTEM_API FXD_GameTime
{
	GENERATED_BODY()

	friend class UXD_GameTimeTypeFunctionLibrary;
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

private:
	static bool InTimeRange(int64 CurTime, int64 StartTime, int64 EndTime)
	{
		return StartTime < EndTime ? CurTime >= StartTime && CurTime < EndTime : CurTime > StartTime || CurTime <= EndTime;
	}

public:
	bool InHourRange(const FXD_EveryHourConfig& StartTime, const FXD_EveryHourConfig& EndTime) const;

	bool InDayRange(const FXD_EveryDayConfig& StartTime, const FXD_EveryDayConfig& EndTime) const;

	bool InWeekRange(const FXD_EveryWeekConfig& StartTime, const FXD_EveryWeekConfig& EndTime) const;

	bool InMonthRange(const FXD_EveryMonthConfig& StartTime, const FXD_EveryMonthConfig& EndTime) const;

	bool InYearRange(const FXD_EveryYearConfig& StartTime, const FXD_EveryYearConfig& EndTime) const;

	bool InSpecialTimeRange(const FXD_SpecialTimeConfig& StartTime, const FXD_SpecialTimeConfig& EndTime) const;
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

	EXD_DayOfWeek GetDayOfWeek() const
	{
		return static_cast<EXD_DayOfWeek>(DateTime.GetDayOfWeek());
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

namespace FXD_GameTimeConfig
{
	static constexpr int64 TicksPerDay = FXD_GameTime::TicksPerDay / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerHour = FXD_GameTime::TicksPerHour / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerMicrosecond = FXD_GameTime::TicksPerMicrosecond / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerMillisecond = FXD_GameTime::TicksPerMillisecond / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerMinute = FXD_GameTime::TicksPerMinute / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerSecond = FXD_GameTime::TicksPerSecond / FXD_GameTime::TicksPerSecond;
	static constexpr int64 TicksPerWeek = FXD_GameTime::TicksPerWeek / FXD_GameTime::TicksPerSecond;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryHourConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryHourConfig"))
struct XD_TIMESYSTEM_API FXD_EveryHourConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryHourConfig() = default;

	FXD_EveryHourConfig(int32 Minute)
		:Ticks(Minute * FXD_GameTimeConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryHourConfig& EveryHourParam) const
	{
		return Ticks == EveryHourParam.Ticks;
	}

	friend uint32 GetTypeHash(const FXD_EveryHourConfig& EveryHourParam)
	{
		return GetTypeHash(EveryHourParam.Ticks);
	}

	void GetConfig(int32& Minute) const
	{
		Minute = Ticks / FXD_GameTimeConfig::TicksPerMinute;
	}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryDayConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryDayConfig"))
struct XD_TIMESYSTEM_API FXD_EveryDayConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryDayConfig() = default;

	FXD_EveryDayConfig(int32 Hour, int32 Minute)
		:Ticks(Hour * FXD_GameTimeConfig::TicksPerHour + Minute * FXD_GameTimeConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryDayConfig& EveryDayParam) const
	{
		return Ticks == EveryDayParam.Ticks;
	}

	friend uint32 GetTypeHash(const FXD_EveryDayConfig& EveryDayParam)
	{
		return GetTypeHash(EveryDayParam.Ticks);
	}

	void GetConfig(int32& Hour, int32& Minute) const
	{
		Hour = Ticks / FXD_GameTimeConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerMinute;
	}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryWeekConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryWeekConfig"))
struct XD_TIMESYSTEM_API FXD_EveryWeekConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryWeekConfig() = default;

	FXD_EveryWeekConfig(int32 WeekDay, int32 Hour, int32 Minute)
		:Ticks(WeekDay * FXD_GameTimeConfig::TicksPerDay + Hour * FXD_GameTimeConfig::TicksPerHour + Minute * FXD_GameTimeConfig::TicksPerMinute)
	{}

	FXD_EveryWeekConfig(EXD_DayOfWeek WeekDay, int32 Hour, int32 Minute)
		:FXD_EveryWeekConfig(static_cast<int32>(WeekDay), Hour, Minute)
	{}

	bool operator==(const FXD_EveryWeekConfig& EveryWeekParam) const
	{
		return Ticks == EveryWeekParam.Ticks;
	}

	friend uint32 GetTypeHash(const FXD_EveryWeekConfig& EveryWeekParam)
	{
		return GetTypeHash(EveryWeekParam.Ticks);
	}

	void GetConfig(int32& WeekDay, int32& Hour, int32& Minute) const
	{
		WeekDay = Ticks / FXD_GameTimeConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfig::TicksPerDay / FXD_GameTimeConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerMinute;
	}

	void GetConfig(EXD_DayOfWeek& WeekDay, int32& Hour, int32& Minute) const
	{
		WeekDay = static_cast<EXD_DayOfWeek>(Ticks / FXD_GameTimeConfig::TicksPerDay);
		Hour = Ticks % FXD_GameTimeConfig::TicksPerDay / FXD_GameTimeConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerMinute;
	}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryMonthConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryMonthConfig"))
struct XD_TIMESYSTEM_API FXD_EveryMonthConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryMonthConfig() = default;

	FXD_EveryMonthConfig(int32 Day, int32 Hour, int32 Minute)
		:Ticks(Day * FXD_GameTimeConfig::TicksPerDay + Hour * FXD_GameTimeConfig::TicksPerHour + Minute * FXD_GameTimeConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryMonthConfig& EveryMonthParam) const
	{
		return Ticks == EveryMonthParam.Ticks;
	}

	void GetConfig(int32& Day, int32& Hour, int32& Minute) const
	{
		Day = Ticks / FXD_GameTimeConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfig::TicksPerDay / FXD_GameTimeConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerMinute;
	}

	friend uint32 GetTypeHash(const FXD_EveryMonthConfig& EveryMonthParam)
	{
		return GetTypeHash(EveryMonthParam.Ticks);
	}

private:
	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryYearConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryYearConfig"))
struct XD_TIMESYSTEM_API FXD_EveryYearConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryYearConfig() = default;

	FXD_EveryYearConfig(int32 Month, int32 Day, int32 Hour, int32 Minute)
		:Month(Month), Ticks(Day * FXD_GameTimeConfig::TicksPerDay + Hour * FXD_GameTimeConfig::TicksPerHour + Minute * FXD_GameTimeConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryYearConfig& EveryYearConfig) const
	{
		return Month == EveryYearConfig.Month && Ticks == EveryYearConfig.Ticks;
	}

	void GetConfig(int32& Month, int32& Day, int32& Hour, int32& Minute) const
	{
		Month = this->Month;
		Day = Ticks / FXD_GameTimeConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfig::TicksPerDay / FXD_GameTimeConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerMinute;
	}

	friend uint32 GetTypeHash(const FXD_EveryYearConfig& EveryYearConfig)
	{
		return HashCombine(GetTypeHash(EveryYearConfig.Month), GetTypeHash(EveryYearConfig.Ticks));
	}

private:
	UPROPERTY()
	uint8 Month;

	UPROPERTY()
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeSpecialTimeConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakSpecialTimeConfig"))
struct XD_TIMESYSTEM_API FXD_SpecialTimeConfig
{
	GENERATED_BODY()

public:
	FXD_SpecialTimeConfig() = default;

	FXD_SpecialTimeConfig(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute)
		:SpecialTime(Year, Month, Day, Hour, Minute)
	{}

	bool operator==(const FXD_SpecialTimeConfig& SpecialTimeConfig) const
	{
		return SpecialTime == SpecialTimeConfig.SpecialTime;
	}

	void GetConfig(int32& Year, int32& Month, int32& Day, int32& Hour, int32& Minute) const
	{
		SpecialTime.GetDate(Year, Month, Day);
		Hour = SpecialTime.GetHour();
		Minute = SpecialTime.GetMinute();
	}

	friend uint32 GetTypeHash(const FXD_SpecialTimeConfig& SpecialTimeConfig)
	{
		return GetTypeHash(SpecialTimeConfig.SpecialTime);
	}

	UPROPERTY(EditAnywhere, Category = "时间系统")
	FXD_GameTime SpecialTime;
};

