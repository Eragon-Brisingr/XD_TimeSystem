// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemType.h"
#include <Kismet/KismetMathLibrary.h>

#define LOCTEXT_NAMESPACE "XD_TimeSystem"

bool FXD_GameTime::InRange(const FXD_GameTime& StartTime, const FXD_GameTime& EndTime) const
{
	const FXD_GameTime& CurrentTime = *this;
	return StartTime < EndTime ? CurrentTime >= StartTime && CurrentTime < EndTime : CurrentTime >= StartTime || CurrentTime < EndTime;
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
