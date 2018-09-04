// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemType.h"
#include <Kismet/KismetMathLibrary.h>

#define LOCTEXT_NAMESPACE "XD_TimeSystem"

bool FXD_GameTime::InHourRange(const FXD_EveryHourConfig& StartTime, const FXD_EveryHourConfig& EndTime) const
{
	return InTimeRange(GetTicks() % TicksPerHour, StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InDayRange(const FXD_EveryDayConfig& StartTime, const FXD_EveryDayConfig& EndTime) const
{
	return InTimeRange(GetTicks() % TicksPerDay, StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InWeekRange(const FXD_EveryWeekConfig& StartTime, const FXD_EveryWeekConfig& EndTime) const
{
	return InTimeRange(GetTicks() % TicksPerWeek, StartTime.Ticks, EndTime.Ticks);
}

bool FXD_GameTime::InMonthRange(const FXD_EveryMonthConfig& StartTime, const FXD_EveryMonthConfig& EndTime) const
{
	int32 StartDay, StartHour, StartMinute, EndDay, EndHour, EndMinute;
	StartTime.GetConfig(StartDay, StartHour, StartMinute);
	EndTime.GetConfig(EndDay, EndHour, EndMinute);
	return InTimeRange(GetTicks(), FXD_GameTime(GetYear(), GetMonth(), StartDay, StartHour, StartMinute).GetTicks(), FXD_GameTime(GetYear(), GetMonth(), EndDay, EndHour, EndMinute).GetTicks());
}

bool FXD_GameTime::InYearRange(const FXD_EveryYearConfig& StartTime, const FXD_EveryYearConfig& EndTime) const
{
	int32 StartMonth, StartDay, StartHour, StartMinute, EndMonth, EndDay, EndHour, EndMinute;
	StartTime.GetConfig(StartMonth, StartDay, StartHour, StartMinute);
	EndTime.GetConfig(EndMonth, EndDay, EndHour, EndMinute);
	return InTimeRange(GetTicks(), FXD_GameTime(GetYear(), StartMonth, StartDay, StartHour, StartMinute).GetTicks(), FXD_GameTime(GetYear(), EndMonth, EndDay, EndHour, EndMinute).GetTicks());
}

bool FXD_GameTime::InSpecialTimeRange(const FXD_SpecialTimeConfig& StartTime, const FXD_SpecialTimeConfig& EndTime) const
{
	return StartTime.GetTicks() < EndTime.GetTicks() ? GetTicks() >= StartTime.GetTicks() && GetTicks() < EndTime.GetTicks() : false;
}

float FXD_GameTime::GetRateInDay() const
{
	return float(GetTicks() % TicksPerDay) / TicksPerDay;
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

#undef LOCTEXT_NAMESPACE
