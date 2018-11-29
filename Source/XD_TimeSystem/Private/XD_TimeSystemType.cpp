// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemType.h"
#include <Kismet/KismetMathLibrary.h>

#define LOCTEXT_NAMESPACE "XD_TimeSystem"
namespace XD_DayOfWeek
{
	FText DayOfWeekToText(EXD_DayOfWeek DayOfWeek)
	{
		switch (DayOfWeek)
		{
		case EXD_DayOfWeek::Monday:
			return LOCTEXT("周一", "周一");
		case EXD_DayOfWeek::Tuesday:
			return LOCTEXT("周二", "周二");
		case EXD_DayOfWeek::Wednesday:
			return LOCTEXT("周三", "周三");
		case EXD_DayOfWeek::Thursday:
			return LOCTEXT("周四", "周四");
		case EXD_DayOfWeek::Friday:
			return LOCTEXT("周五", "周五");
		case EXD_DayOfWeek::Saturday:
			return LOCTEXT("周六", "周六");
		case EXD_DayOfWeek::Sunday:
			return LOCTEXT("周日", "周日");
		}
		return LOCTEXT("未定义", "未定义");
	}
}

bool FXD_GameTime::InTimeRange(int64 CurTime, int64 StartTime, int64 EndTime)
{
	return StartTime < EndTime ? CurTime >= StartTime && CurTime < EndTime : CurTime >= StartTime || CurTime < EndTime;
}

int64 FXD_GameTime::EveryMonthToCurrentTicks(const FXD_EveryMonthConfig& EveryMonthConfig) const
{
	int32 Day, Hour, Minute;
	EveryMonthConfig.GetConfig(Day, Hour, Minute);
	return FXD_GameTime(GetYear(), GetMonth(), Day, Hour, Minute).GetTicks();
}

int64 FXD_GameTime::EveryYearToCurrentTicks(const FXD_EveryYearConfig& EveryYearConfig) const
{
	int32 Month, Day, Hour, Minute;
	EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
	return FXD_GameTime(GetYear(), Month, Day, Hour, Minute).GetTicks();
}

bool FXD_GameTime::InHourRange(const FXD_EveryHourConfig& StartTime, const FXD_EveryHourConfig& EndTime) const
{
	return InTimeRange(ToEveryHourTicks(), StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InDayRange(const FXD_EveryDayConfig& StartTime, const FXD_EveryDayConfig& EndTime) const
{
	return InTimeRange(ToEveryDayTicks(), StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InWeekRange(const FXD_EveryWeekConfig& StartTime, const FXD_EveryWeekConfig& EndTime) const
{
	return InTimeRange(ToEveryWeekTicks(), StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InMonthRange(const FXD_EveryMonthConfig& StartTime, const FXD_EveryMonthConfig& EndTime) const
{
	return InTimeRange(GetTicks(), EveryMonthToCurrentTicks(StartTime), EveryMonthToCurrentTicks(EndTime));
}

bool FXD_GameTime::InYearRange(const FXD_EveryYearConfig& StartTime, const FXD_EveryYearConfig& EndTime) const
{
	return InTimeRange(GetTicks(), EveryYearToCurrentTicks(StartTime), EveryYearToCurrentTicks(EndTime));
}

bool FXD_GameTime::InSpecialTimeRange(const FXD_SpecialTimeConfig& StartTime, const FXD_SpecialTimeConfig& EndTime) const
{
	return StartTime.GetTicks() < EndTime.GetTicks() ? GetTicks() >= StartTime.GetTicks() && GetTicks() < EndTime.GetTicks() : false;
}

float FXD_GameTime::GetRateInDay() const
{
	return float(GetTicks() % FXD_GameTimeConfig::TicksPerDay) / FXD_GameTimeConfig::TicksPerDay;
}

bool FXD_GameTime::operator==(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() == Other.GetTicks();
}

bool FXD_GameTime::operator!=(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() != Other.GetTicks();
}

bool FXD_GameTime::operator>(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() > Other.GetTicks();
}

bool FXD_GameTime::operator>=(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() >= Other.GetTicks();
}

bool FXD_GameTime::operator<(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() < Other.GetTicks();
}

bool FXD_GameTime::operator<=(const FXD_SpecialTimeConfig& Other) const
{
	return ToEveryWeekTicks() <= Other.GetTicks();
}

FText FXD_GameTime::ToText() const
{
	int32 Year, Month, Day, Hour, Minute, Second, Millisecond;
	UKismetMathLibrary::BreakDateTime(DateTime, Year, Month, Day, Hour, Minute, Second, Millisecond);
	return FText::Format(LOCTEXT("GameTimeToText Format", "{0}年{1}月{2}日{3}时{4}分{5}秒{6}毫秒"), Year, Month, Day, Hour, Minute, Second, Millisecond);
}

FString FXD_GameTime::ToString() const
{
	return ToText().ToString();
}

FString FXD_EveryHourConfig::ToString() const
{
	int Minute;
	GetConfig(Minute);
	return FString::Printf(TEXT("%d分"), Minute);
}

FString FXD_EveryDayConfig::ToString() const
{
	int Hour, Minute;
	GetConfig(Hour, Minute);
	return FString::Printf(TEXT("%d时 %d分"), Hour, Minute);
}

FString FXD_EveryWeekConfig::ToString() const
{
	int Hour, Minute;
	EXD_DayOfWeek DayOfWeek;
	GetConfig(DayOfWeek, Hour, Minute);
	return FString::Printf(TEXT("%s %d时 %d分"), *XD_DayOfWeek::DayOfWeekToText(DayOfWeek).ToString(), Hour, Minute);
}

void FXD_EveryMonthConfig::GetConfigSafe(int32 Year, int32 Month, int32& Day, int32& Hour, int32& Minute) const
{
	GetConfig(Day, Hour, Minute);

	int32 ValidDayOfMonth = FXD_GameTime::DaysInMonth(Year, Month);
	if (Day > ValidDayOfMonth)
	{
		Day = ValidDayOfMonth;
	}
}

FString FXD_EveryMonthConfig::ToString() const
{
	int Day, Hour, Minute;
	GetConfig(Day, Hour, Minute);
	return FString::Printf(TEXT("%d日 %d时 %d分"), Day, Hour, Minute);
}

void FXD_EveryYearConfig::GetConfigSafe(int32 Year, int32& OutMonth, int32& Day, int32& Hour, int32& Minute) const
{
	GetConfig(OutMonth, Day, Hour, Minute);
	int32 ValidDayOfMonth = FXD_GameTime::DaysInMonth(Year, OutMonth);
	if (Day > ValidDayOfMonth)
	{
		Day = ValidDayOfMonth;
	}
}

FString FXD_EveryYearConfig::ToString() const
{
	int Month, Day, Hour, Minute;
	GetConfig(Month, Day, Hour, Minute);
	return FString::Printf(TEXT("%d月 %d日 %d时 %d分"), Month, Day, Hour, Minute);
}

#undef LOCTEXT_NAMESPACE
