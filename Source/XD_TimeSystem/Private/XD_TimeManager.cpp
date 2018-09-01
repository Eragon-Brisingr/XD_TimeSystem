// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeManager.h"
#include <UnrealNetwork.h>
#include "XD_TimeSystemUtility.h"
#include "XD_TimeSystem_GameStateInterface.h"
#include <GameFramework/GameStateBase.h>


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
		for (FXD_GameTime InterpGameTime((PreMinutes + 1) * FXD_GameTime::TicksPerMinute); InterpGameTime <= CurMinutes  * FXD_GameTime::TicksPerMinute; InterpGameTime += FXD_GameTime::TicksPerMinute)
		{
			int32 InterpYear, InterpMonth, InterpDay;
			InterpGameTime.GetDate(InterpYear, InterpMonth, InterpDay);
			int32 InterpHour = InterpGameTime.GetHour();
			int32 InterpMinute = InterpGameTime.GetMinute();
			EXD_DayOfWeek InterpWeekDay = InterpGameTime.GetDayOfWeek();

			//Every Hour
			{
				if (TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(FXD_EveryHourConfig(InterpMinute)))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

			//Every Day
			{
				if (TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(FXD_EveryDayConfig(InterpHour, InterpMinute)))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

			//Every Week
			{
				if (TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(FXD_EveryWeekDayConfig(InterpWeekDay, InterpHour, InterpMinute)))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

 			//Every Month
 			{
 				if (TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(FXD_EveryMonthConfig(InterpDay, InterpHour, InterpMinute)))
 				{
 					InvokeExecuteGameTimeEvents(*Events);
 				}
 			}

			//Every Year
			{
				if (TArray<FXD_GameTimeEvent>* Events = EveryYearEvents.Find(FXD_EveryYearConfig(InterpMonth, InterpDay, InterpHour, InterpMinute)))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}

			//Special Time
			{
				if (TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(FXD_SpecialTimeConfig(InterpYear, InterpMonth, InterpDay, InterpHour, InterpMinute)))
				{
					InvokeExecuteGameTimeEvents(*Events);
				}
			}
		}
	}
}

void UXD_TimeManager::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXD_TimeManager, CurrentTime, COND_InitialOnly);
	DOREPLIFETIME(UXD_TimeManager, CurrentTime);
}

UXD_TimeManager* UXD_TimeManager::GetGameTimeManager(const UObject* WorldContextObject)
{
	AGameStateBase* GameState = WorldContextObject->GetWorld()->GetGameState();
	if (GameState->Implements<UXD_TimeSystem_GameStateInterface>())
	{
		return IXD_TimeSystem_GameStateInterface::Execute_GetGameTimeManager(GameState);
	}
	else if (UXD_TimeManager* TimeManager = GameState->FindComponentByClass<UXD_TimeManager>())
	{
		TimeSystem_Warning_LOG("请在GameState继承接口XD_TimeSystem_GameStateInterface并实现GetGameTimeManager");
		return TimeManager;
	}
	TimeSystem_Warning_LOG("请在GameState中添加TimeManager组件，并继承接口XD_TimeSystem_GameStateInterface并实现GetGameTimeManager");
	return nullptr;
}

void UXD_TimeManager::AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent)
{
	EveryHourEvents.FindOrAdd(EveryHourConfig).Add(EveryHourEvent);
}

void UXD_TimeManager::AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent)
{
	EveryDayEvents.FindOrAdd(EveryDayConfig).Add(EveryDayEvent);
}

void UXD_TimeManager::AddEveryWeekDayEvent_Instant(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent)
{
	EveryWeekDayEvents.FindOrAdd(EveryWeekDayConfig).Add(EveryWeekDayEvent);
}

void UXD_TimeManager::AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent)
{
	EveryMonthEvents.FindOrAdd(EveryMonthConfig).Add(EveryMonthEvent);
}

void UXD_TimeManager::AddEveryYearEvent_Instant(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent)
{
	EveryYearEvents.FindOrAdd(EveryYearConfig).Add(EveryYearEvent);
}

void UXD_TimeManager::AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent)
{
	SpecialTimeEvents.FindOrAdd(SpecialTimeConfig).Add(EveryYearEvent);
}

void UXD_TimeManager::RemoveEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(EveryHourConfig))
	{
		Events->RemoveSingle(EveryHourEvent);
	}
}

void UXD_TimeManager::RemoveEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(EveryDayConfig))
	{
		Events->RemoveSingle(EveryDayEvent);
	}
}

void UXD_TimeManager::RemoveEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(EveryWeekDayConfig))
	{
		Events->RemoveSingle(EveryWeekDayEvent);
	}
}

void UXD_TimeManager::RemoveEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(EveryMonthConfig))
	{
		Events->RemoveSingle(EveryMonthEvent);
	}
}

void UXD_TimeManager::RemoveEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryYearEvents.Find(EveryYearConfig))
	{
		Events->RemoveSingle(EveryYearEvent);
	}
}

void UXD_TimeManager::RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(SpecialTimeConfig))
	{
		Events->RemoveSingle(EveryYearEvent);
	}
}

bool UXD_TimeManager::ContainsEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(EveryHourConfig))
	{
		return Events->Contains(EveryHourEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(EveryDayConfig))
	{
		return Events->Contains(EveryDayEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(EveryWeekDayConfig))
	{
		return Events->Contains(EveryWeekDayEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(EveryMonthConfig))
	{
		return Events->Contains(EveryMonthEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryYearEvents.Find(EveryYearConfig))
	{
		return Events->Contains(EveryYearEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(SpecialTimeConfig))
	{
		return Events->Contains(EveryYearEvent);
	}
	return false;
}

