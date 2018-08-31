// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemFunctionLibrary.h"
#include <Kismet/KismetMathLibrary.h>


#define LOCTEXT_NAMESPACE "XD_TimeSystem"

FXD_GameTime UXD_TimeSystemFunctionLibrary::MakeGameTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second, int32 Millisecond)
{
	return FXD_GameTime(Year, Month, Day, Hour, Minute, Second, Millisecond);
}

void UXD_TimeSystemFunctionLibrary::BreakGameTime(FXD_GameTime Time, int32& Year, int32& Month, int32& Day, int32& Hour, int32& Minute, int32& Second, int32& Millisecond)
{
	UKismetMathLibrary::BreakDateTime(Time.DateTime, Year, Month, Day, Hour, Minute, Second, Millisecond);
}

FText UXD_TimeSystemFunctionLibrary::GameTimeToText(FXD_GameTime Time)
{
	return Time.ToText();
}

FString UXD_TimeSystemFunctionLibrary::GameTimeToString(FXD_GameTime Time)
{
	return Time.ToString();
}

#undef LOCTEXT_NAMESPACE
