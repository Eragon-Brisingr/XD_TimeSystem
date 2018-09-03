// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemFunctionLibraryEx.h"
#include "XD_TimeManager.h"




float UXD_TimeSystemFunctionLibraryEx::GetMoonPhaseRate(const UObject* WorldContextObject)
{
	if (UXD_TimeManager* TimeManager = UXD_TimeManager::GetGameTimeManager(WorldContextObject))
	{
		return double(TimeManager->CurrentTime.GetTicks() % TicksPreLunarMonth) / TicksPreLunarMonth;
	}
	return 0.f;
}
