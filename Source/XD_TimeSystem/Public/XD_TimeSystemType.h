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

USTRUCT()
struct FXD_GameTimeEvents
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	TArray<FXD_GameTimeEvent> GameTimeEvents;
};

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

namespace XD_DayOfWeek
{
	XD_TIMESYSTEM_API FText DayOfWeekToText(EXD_DayOfWeek DayOfWeek);
}

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeGameTimeSpan", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakGameTimeSpan"))
struct XD_TIMESYSTEM_API FXD_GameTimeSpan
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_GameTimeSpan() = default;

	FXD_GameTimeSpan(int64 Ticks)
		:Timespan(Ticks)
	{}

	FXD_GameTimeSpan(int32 Days, int32 Hours, int32 Minutes, int32 Seconds = 0, int32 FractionNano = 0)
		:Timespan(Days, Hours, Minutes, Seconds, FractionNano)
	{}

	int64 GetTicks() const
	{
		return Timespan.GetTicks();
	}

	int32 GetDays() const
	{
		return Timespan.GetDays();
	}

	int32 GetHours() const
	{
		return Timespan.GetHours();
	}

	int32 GetMinutes() const
	{
		return Timespan.GetMinutes();
	}

	int32 GetSeconds() const
	{
		return Timespan.GetSeconds();
	}

	FXD_GameTimeSpan GetDuration() const
	{
		return FXD_GameTimeSpan(Timespan);
	}

	double GetTotalDays() const
	{
		return Timespan.GetTotalDays();
	}

	double GetTotalHours() const
	{
		return Timespan.GetTotalHours();
	}

	double GetTotalMinutes() const
	{
		return Timespan.GetTotalMinutes();
	}

	double GetTotalSeconds() const
	{
		return Timespan.GetTotalSeconds();
	}

	static FXD_GameTimeSpan FromDays(double Days)
	{
		return FXD_GameTimeSpan(FTimespan::FromDays(Days));
	}

	static FXD_GameTimeSpan FromHours(double Hours)
	{
		return FXD_GameTimeSpan(FTimespan::FromHours(Hours));
	}

	static FXD_GameTimeSpan FromMinutes(double Minutes)
	{
		return FXD_GameTimeSpan(FTimespan::FromMinutes(Minutes));
	}

	static FXD_GameTimeSpan FromSeconds(double Seconds)
	{
		return FXD_GameTimeSpan(FTimespan::FromSeconds(Seconds));
	}
private:
	FXD_GameTimeSpan(FTimespan Timespan)
		:Timespan(Timespan)
	{}

	UPROPERTY(EditAnywhere, SaveGame)
	FTimespan Timespan;
};

namespace FXD_GameTimeConfig
{
	//100ns == 1Tick
	static constexpr int64 NanosecondsPerTick = ETimespan::NanosecondsPerTick;
	static constexpr int64 TicksPerDay = ETimespan::TicksPerDay;
	static constexpr int64 TicksPerHour = ETimespan::TicksPerHour;
	static constexpr int64 TicksPerMicrosecond = ETimespan::TicksPerMicrosecond;
	static constexpr int64 TicksPerMillisecond = ETimespan::TicksPerMillisecond;
	static constexpr int64 TicksPerMinute = ETimespan::TicksPerMinute;
	static constexpr int64 TicksPerSecond = ETimespan::TicksPerSecond;
	static constexpr int64 TicksPerWeek = ETimespan::TicksPerWeek;
}

namespace FXD_GameTimeConfigConfig
{
	static constexpr int64 Rate = FXD_GameTimeConfig::TicksPerSecond;

	static constexpr int64 TicksPerDay = FXD_GameTimeConfig::TicksPerDay / FXD_GameTimeConfig::TicksPerSecond;
	static constexpr int64 TicksPerHour = FXD_GameTimeConfig::TicksPerHour / FXD_GameTimeConfig::TicksPerSecond;
	static constexpr int64 TicksPerMicrosecond = FXD_GameTimeConfig::TicksPerMicrosecond / FXD_GameTimeConfig::TicksPerSecond;
	static constexpr int64 TicksPerMillisecond = FXD_GameTimeConfig::TicksPerMillisecond / FXD_GameTimeConfig::TicksPerSecond;
	static constexpr int64 TicksPerMinute = FXD_GameTimeConfig::TicksPerMinute / FXD_GameTimeConfig::TicksPerSecond;
	static constexpr int64 TicksPerSecond = FXD_GameTimeConfig::TicksPerSecond / Rate;
	static constexpr int64 TicksPerWeek = FXD_GameTimeConfig::TicksPerWeek / FXD_GameTimeConfig::TicksPerSecond;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryHourConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryHourConfig"))
struct XD_TIMESYSTEM_API FXD_EveryHourConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryHourConfig() = default;

	FXD_EveryHourConfig(int32 Minute)
		:Ticks(Minute * FXD_GameTimeConfigConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryHourConfig& EveryHourParam) const
	{
		return Ticks == EveryHourParam.Ticks;
	}
	bool operator<(const FXD_EveryHourConfig& Ohter) const { return Ticks < Ohter.Ticks; }

	friend uint32 GetTypeHash(const FXD_EveryHourConfig& EveryHourParam)
	{
		return GetTypeHash(EveryHourParam.Ticks);
	}

	void GetConfig(int32& Minute) const
	{
		Minute = Ticks / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	FString ToString() const;
private:
	UPROPERTY(EditAnywhere, SaveGame)
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
		:Ticks(Hour * FXD_GameTimeConfigConfig::TicksPerHour + Minute * FXD_GameTimeConfigConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryDayConfig& EveryDayParam) const
	{
		return Ticks == EveryDayParam.Ticks;
	}
	bool operator<(const FXD_EveryDayConfig& Ohter) const { return Ticks < Ohter.Ticks; }

	friend uint32 GetTypeHash(const FXD_EveryDayConfig& EveryDayParam)
	{
		return GetTypeHash(EveryDayParam.Ticks);
	}

	void GetConfig(int32& Hour, int32& Minute) const
	{
		Hour = Ticks / FXD_GameTimeConfigConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfigConfig::TicksPerHour / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	FString ToString() const;
private:
	UPROPERTY(EditAnywhere, SaveGame)
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
		:Ticks(WeekDay * FXD_GameTimeConfigConfig::TicksPerDay + Hour * FXD_GameTimeConfigConfig::TicksPerHour + Minute * FXD_GameTimeConfigConfig::TicksPerMinute)
	{}

	FXD_EveryWeekConfig(EXD_DayOfWeek WeekDay, int32 Hour, int32 Minute)
		:FXD_EveryWeekConfig(static_cast<int32>(WeekDay), Hour, Minute)
	{}

	bool operator==(const FXD_EveryWeekConfig& EveryWeekParam) const
	{
		return Ticks == EveryWeekParam.Ticks;
	}
	bool operator<(const FXD_EveryWeekConfig& Ohter) const { return Ticks < Ohter.Ticks; }

	friend uint32 GetTypeHash(const FXD_EveryWeekConfig& EveryWeekParam)
	{
		return GetTypeHash(EveryWeekParam.Ticks);
	}

	void GetConfig(int32& WeekDay, int32& Hour, int32& Minute) const
	{
		WeekDay = Ticks / FXD_GameTimeConfigConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfigConfig::TicksPerDay / FXD_GameTimeConfigConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfigConfig::TicksPerHour / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	void GetConfig(EXD_DayOfWeek& WeekDay, int32& Hour, int32& Minute) const
	{
		WeekDay = static_cast<EXD_DayOfWeek>(Ticks / FXD_GameTimeConfigConfig::TicksPerDay);
		Hour = Ticks % FXD_GameTimeConfigConfig::TicksPerDay / FXD_GameTimeConfigConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfigConfig::TicksPerHour / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	FString ToString() const;
private:
	UPROPERTY(EditAnywhere, SaveGame)
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryMonthConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryMonthConfig"))
struct XD_TIMESYSTEM_API FXD_EveryMonthConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryMonthConfig()
		:FXD_EveryMonthConfig(1, 0, 0)
	{}

	FXD_EveryMonthConfig(int32 Day, int32 Hour, int32 Minute)
		:Ticks(Day * FXD_GameTimeConfigConfig::TicksPerDay + Hour * FXD_GameTimeConfigConfig::TicksPerHour + Minute * FXD_GameTimeConfigConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryMonthConfig& EveryMonthParam) const
	{
		return Ticks == EveryMonthParam.Ticks;
	}
	bool operator<(const FXD_EveryMonthConfig& Ohter) const { return Ticks < Ohter.Ticks; }

	void GetConfig(int32& Day, int32& Hour, int32& Minute) const
	{
		Day = Ticks / FXD_GameTimeConfigConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfigConfig::TicksPerDay / FXD_GameTimeConfigConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfigConfig::TicksPerHour / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	friend uint32 GetTypeHash(const FXD_EveryMonthConfig& EveryMonthParam)
	{
		return GetTypeHash(EveryMonthParam.Ticks);
	}

	FString ToString() const;
private:
	UPROPERTY(EditAnywhere, SaveGame)
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeEveryYearConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakEveryYearConfig"))
struct XD_TIMESYSTEM_API FXD_EveryYearConfig
{
	GENERATED_BODY()

	friend struct FXD_GameTime;
public:
	FXD_EveryYearConfig()
		:FXD_EveryYearConfig(1, 1, 0, 0)
	{}

	FXD_EveryYearConfig(int32 Month, int32 Day, int32 Hour, int32 Minute)
		:Month(Month), Ticks(Day * FXD_GameTimeConfigConfig::TicksPerDay + Hour * FXD_GameTimeConfigConfig::TicksPerHour + Minute * FXD_GameTimeConfigConfig::TicksPerMinute)
	{}

	bool operator==(const FXD_EveryYearConfig& EveryYearConfig) const
	{
		return Month == EveryYearConfig.Month && Ticks == EveryYearConfig.Ticks;
	}
	bool operator<(const FXD_EveryYearConfig& Ohter) const { return Month < Ohter.Month ? true : Ticks < Ohter.Ticks; }

	void GetConfig(int32& OutMonth, int32& Day, int32& Hour, int32& Minute) const
	{
		OutMonth = Month;
		Day = Ticks / FXD_GameTimeConfigConfig::TicksPerDay;
		Hour = Ticks % FXD_GameTimeConfigConfig::TicksPerDay / FXD_GameTimeConfigConfig::TicksPerHour;
		Minute = Ticks % FXD_GameTimeConfigConfig::TicksPerHour / FXD_GameTimeConfigConfig::TicksPerMinute;
	}

	friend uint32 GetTypeHash(const FXD_EveryYearConfig& EveryYearConfig)
	{
		return HashCombine(GetTypeHash(EveryYearConfig.Month), GetTypeHash(EveryYearConfig.Ticks));
	}

	FString ToString() const;
private:
	UPROPERTY(EditAnywhere, SaveGame)
	uint8 Month;

	UPROPERTY(EditAnywhere, SaveGame)
	int32 Ticks;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeGameTime", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakGameTime"))
struct XD_TIMESYSTEM_API FXD_GameTime
{
	GENERATED_BODY()

	friend class UXD_GameTimeTypeFunctionLibrary;
public:
	FXD_GameTime()
		:FXD_GameTime(1000, 1, 1, 0, 0, 0, 0)
	{}
	FXD_GameTime(int64 InTicks) : DateTime(InTicks) {}
	FXD_GameTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second = 0, int32 Millisecond = 0)
		:DateTime(Year, Month, Day, Hour, Minute, Second, Millisecond) {}

private:
	//使用FDateTime的实现，不使用继承否则没法SaveGame
	UPROPERTY(EditAnywhere, SaveGame)
	FDateTime DateTime;

private:
	static bool InTimeRange(int64 CurTime, int64 StartTime, int64 EndTime);

	int64 ToEveryHourTicks() const { return (GetTicks() / FXD_GameTimeConfigConfig::Rate) % FXD_GameTimeConfigConfig::TicksPerHour; }
	int64 ToEveryDayTicks() const { return (GetTicks() / FXD_GameTimeConfigConfig::Rate) % FXD_GameTimeConfigConfig::TicksPerDay; }
	int64 ToEveryWeekTicks() const { return (GetTicks() / FXD_GameTimeConfigConfig::Rate) % FXD_GameTimeConfigConfig::TicksPerWeek; }
	int64 EveryMonthToCurrentTicks(const FXD_EveryMonthConfig& EveryMonthConfig) const;
	int64 EveryYearToCurrentTicks(const FXD_EveryYearConfig& EveryYearConfig) const;
public:
	bool InHourRange(const FXD_EveryHourConfig& StartTime, const FXD_EveryHourConfig& EndTime) const;
	bool operator==(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() == Other.Ticks; }
	bool operator!=(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() != Other.Ticks; }
	bool operator>(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() > Other.Ticks; }
	bool operator>=(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() >= Other.Ticks; }
	bool operator<(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() < Other.Ticks; }
	bool operator<=(const FXD_EveryHourConfig& Other) const { return ToEveryHourTicks() <= Other.Ticks; }

	bool InDayRange(const FXD_EveryDayConfig& StartTime, const FXD_EveryDayConfig& EndTime) const;
	bool operator==(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() == Other.Ticks; }
	bool operator!=(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() != Other.Ticks; }
	bool operator>(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() > Other.Ticks; }
	bool operator>=(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() >= Other.Ticks; }
	bool operator<(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() < Other.Ticks; }
	bool operator<=(const FXD_EveryDayConfig& Other) const { return ToEveryDayTicks() <= Other.Ticks; }

	bool InWeekRange(const FXD_EveryWeekConfig& StartTime, const FXD_EveryWeekConfig& EndTime) const;
	bool operator==(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() == Other.Ticks; }
	bool operator!=(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() != Other.Ticks; }
	bool operator>(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() > Other.Ticks; }
	bool operator>=(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() >= Other.Ticks; }
	bool operator<(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() < Other.Ticks; }
	bool operator<=(const FXD_EveryWeekConfig& Other) const { return ToEveryWeekTicks() <= Other.Ticks; }

	bool InMonthRange(const FXD_EveryMonthConfig& StartTime, const FXD_EveryMonthConfig& EndTime) const;
	bool operator==(const FXD_EveryMonthConfig& Other) const { return GetTicks() == EveryMonthToCurrentTicks(Other); }
	bool operator!=(const FXD_EveryMonthConfig& Other) const { return GetTicks() != EveryMonthToCurrentTicks(Other); }
	bool operator>(const FXD_EveryMonthConfig& Other) const { return GetTicks() > EveryMonthToCurrentTicks(Other); }
	bool operator>=(const FXD_EveryMonthConfig& Other) const { return GetTicks() >= EveryMonthToCurrentTicks(Other); }
	bool operator<(const FXD_EveryMonthConfig& Other) const { return GetTicks() < EveryMonthToCurrentTicks(Other); }
	bool operator<=(const FXD_EveryMonthConfig& Other) const { return GetTicks() <= EveryMonthToCurrentTicks(Other); }

	bool InYearRange(const FXD_EveryYearConfig& StartTime, const FXD_EveryYearConfig& EndTime) const;
	bool operator==(const FXD_EveryYearConfig& Other) const { return GetTicks() == EveryYearToCurrentTicks(Other); }
	bool operator!=(const FXD_EveryYearConfig& Other) const { return GetTicks() != EveryYearToCurrentTicks(Other); }
	bool operator>(const FXD_EveryYearConfig& Other) const { return GetTicks() > EveryYearToCurrentTicks(Other); }
	bool operator>=(const FXD_EveryYearConfig& Other) const { return GetTicks() >= EveryYearToCurrentTicks(Other); }
	bool operator<(const FXD_EveryYearConfig& Other) const { return GetTicks() < EveryYearToCurrentTicks(Other); }
	bool operator<=(const FXD_EveryYearConfig& Other) const { return GetTicks() <= EveryYearToCurrentTicks(Other); }

	bool InSpecialTimeRange(const FXD_SpecialTimeConfig& StartTime, const FXD_SpecialTimeConfig& EndTime) const;
	bool operator==(const FXD_SpecialTimeConfig& Other) const;
	bool operator!=(const FXD_SpecialTimeConfig& Other) const;
	bool operator>(const FXD_SpecialTimeConfig& Other) const;
	bool operator>=(const FXD_SpecialTimeConfig& Other) const;
	bool operator<(const FXD_SpecialTimeConfig& Other) const;
	bool operator<=(const FXD_SpecialTimeConfig& Other) const;
public:
	float GetRateInDay() const;

public:
	FXD_GameTime operator+(const FXD_GameTimeSpan& Other) const
	{
		return FXD_GameTime(DateTime.GetTicks() + Other.GetTicks());
	}

	FXD_GameTime& operator+=(const FXD_GameTimeSpan& Other)
	{
		DateTime += Other.GetTicks();
		return *this;
	}

	FXD_GameTimeSpan operator-(const FXD_GameTime& Other) const
	{
		return FXD_GameTimeSpan(GetTicks() - Other.GetTicks());
	}

	FXD_GameTime operator-(const FXD_GameTimeSpan& Other) const
	{
		return FXD_GameTime(DateTime.GetTicks() - Other.GetTicks());
	}

	FXD_GameTime& operator-=(const FXD_GameTimeSpan& Other)
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

	FXD_GameTimeSpan GetTimeOfDay() const
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

USTRUCT(BlueprintType, meta = (HasNativeMake = "XD_GameTimeTypeFunctionLibrary.MakeSpecialTimeConfig", HasNativeBreak = "XD_GameTimeTypeFunctionLibrary.BreakSpecialTimeConfig"))
struct XD_TIMESYSTEM_API FXD_SpecialTimeConfig
{
	GENERATED_BODY()

	friend class FXD_SpecialTimeConfig_Customization;
public:
	FXD_SpecialTimeConfig()
		:FXD_SpecialTimeConfig(1000, 1, 1, 0, 0)
	{}

	FXD_SpecialTimeConfig(const FXD_GameTime& GameTime)
		:SpecialTime(GameTime)
	{}

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

	int64 GetTicks() const
	{
		return SpecialTime.GetTicks();
	}
private:
	UPROPERTY(EditAnywhere, Category = "时间系统", SaveGame)
	FXD_GameTime SpecialTime;
};
