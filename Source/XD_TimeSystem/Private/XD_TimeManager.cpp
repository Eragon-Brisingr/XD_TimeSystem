// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeManager.h"
#include <UnrealNetwork.h>
#include "XD_TimeSystemUtility.h"


// Sets default values for this component's properties
UXD_TimeManager::UXD_TimeManager()
	:CurrentTime(1000, 1, 1, 0, 0, 0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UXD_TimeManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UXD_TimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	int64 PreTicks = CurrentTime.GetTicks();
	CurrentTime += DeltaTime * FXD_GameTime::TicksPerSecond * TimeSpendRate;

// 	//Every Second
// 	int64 PreSeconds = PreTicks / FXD_GameTime::TicksPerSecond;
// 	int64 CurSeconds = CurrentTime.GetTicks() / FXD_GameTime::TicksPerSecond;
// 	int64 SpendSceonds = CurSeconds - PreSeconds;
// 	if (SpendSceonds > 0)
// 	{
// 
// 	}

	int64 PreMinutes = PreTicks / FXD_GameTime::TicksPerMinute;
	int64 CurMinutes = CurrentTime.GetTicks() / FXD_GameTime::TicksPerMinute;
	int64 SpendMinutes = CurMinutes - PreMinutes;
	if (SpendMinutes > 0)
	{
		for (int64 InterpTicks = (PreMinutes + 1) * FXD_GameTime::TicksPerMinute; InterpTicks <= CurMinutes  * FXD_GameTime::TicksPerMinute; InterpTicks += FXD_GameTime::TicksPerMinute)
		{
			//Every Hour
			{
				FXD_EveryHourConfig EveryHourConfig;
				EveryHourConfig.Ticks = InterpTicks % FXD_GameTime::TicksPerHour;
				if (TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(EveryHourConfig))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

			//Every Day
			{
				int64 PreHours = InterpTicks / FXD_GameTime::TicksPerHour;
				int64 CurHours = CurrentTime.GetTicks() / FXD_GameTime::TicksPerHour;
				int64 SpendHours = CurHours - PreHours;
				FXD_EveryDayConfig EveryDayConfig;
				EveryDayConfig.Ticks = InterpTicks % FXD_GameTime::TicksPerDay;
				if (TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(EveryDayConfig))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

			//Every Week
			{
				int64 PreWeeks = InterpTicks / FXD_GameTime::TicksPerWeek;
				int64 CurWeeks = CurrentTime.GetTicks() / FXD_GameTime::TicksPerWeek;
				int64 SpendWeeks = CurWeeks - PreWeeks;
				FXD_EveryWeekDayConfig EveryWeekConfig;
				EveryWeekConfig.Ticks = InterpTicks % FXD_GameTime::TicksPerWeek;
				if (TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(EveryWeekConfig))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

// 			//Every Month
// 			{
// 				int64 PreDays = InterpTicks / FXD_GameTime::TicksPerDay;
// 				int64 CurDays = CurrentTime.GetTicks() / FXD_GameTime::TicksPerDay;
// 				int64 SpendDays = CurDays - PreDays;
// 				FXD_EveryMonthConfig EveryMonthConfig;
// 				EveryMonthConfig.Ticks = InterpTicks;
// 				if (TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(EveryMonthConfig))
// 				{
// 					InvokeExecuteGameTimeEvents(*Events);
// 				}
// 			}
		}
	}
}

void UXD_TimeManager::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXD_TimeManager, CurrentTime, COND_InitialOnly);
	DOREPLIFETIME(UXD_TimeManager, CurrentTime);
}

