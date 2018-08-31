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

	//Every Minute
	int64 PreMinutes = PreTicks / FXD_GameTime::TicksPerMinute;
	int64 CurMinutes = CurrentTime.GetTicks() / FXD_GameTime::TicksPerMinute;
	int64 SpendMinutes = CurMinutes - PreMinutes;
	if (SpendMinutes > 0)
	{
		//Every Hour
		int64 PreHours = PreTicks / FXD_GameTime::TicksPerHour;
		int64 CurHours = CurrentTime.GetTicks() / FXD_GameTime::TicksPerHour;
		int64 SpendHours = CurHours - PreHours;
		if (SpendHours > 0)
		{

		}

		//Every Day
		int64 PreDays = PreTicks / FXD_GameTime::TicksPerDay;
		int64 CurDays = CurrentTime.GetTicks() / FXD_GameTime::TicksPerDay;
		int64 SpendDays = CurDays - PreDays;
		if (SpendDays > 0)
		{

		}

		//Every Week
		int64 PreWeeks = PreTicks / FXD_GameTime::TicksPerWeek;
		int64 CurWeeks = CurrentTime.GetTicks() / FXD_GameTime::TicksPerWeek;
		int64 SpendWeeks = CurWeeks - PreWeeks;
		if (SpendWeeks > 0)
		{

		}
	}
}

void UXD_TimeManager::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXD_TimeManager, CurrentTime, COND_InitialOnly);
	DOREPLIFETIME(UXD_TimeManager, CurrentTime);
}

