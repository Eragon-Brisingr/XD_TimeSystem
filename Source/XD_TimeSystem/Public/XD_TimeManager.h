// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XD_SaveGameInterface.h"
#include "XD_TimeSystemType.h"
#include "XD_TimeManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XD_TIMESYSTEM_API UXD_TimeManager : public UActorComponent, public IXD_SaveGameInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXD_TimeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated, SaveGame)
	FXD_GameTime CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated)
	float TimeSpendRate = 20.f;

	TMap<FXD_EveryHourConfig, TArray<FXD_GameTimeEvent>> EveryHourEvents;

	TMap<FXD_EveryDayConfig, TArray<FXD_GameTimeEvent>> EveryDayEvents;

	TMap<FXD_EveryMonthConfig, TArray<FXD_GameTimeEvent>> EveryMonthEvents;

	TMap<FXD_EveryWeekDayConfig, TArray<FXD_GameTimeEvent>> EveryWeekDayEvents;

	void InvokeExecuteGameTimeEvents(const TArray<FXD_GameTimeEvent>& GameTimeEvents)
	{
		for (const FXD_GameTimeEvent& GameTimeEvent : GameTimeEvents)
		{
			GameTimeEvent.ExecuteIfBound();
		}
	}

public:
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent)
	{
		EveryHourEvents.FindOrAdd(EveryHourConfig).Add(EveryHourEvent);
	}

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent)
	{
		EveryDayEvents.FindOrAdd(EveryDayConfig).Add(EveryDayEvent);
	}

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryDayEvent)
	{
		EveryMonthEvents.FindOrAdd(EveryMonthConfig).Add(EveryDayEvent);
	}

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryWeekDayEvent_Instant(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryDayEvent)
	{
		EveryWeekDayEvents.FindOrAdd(EveryWeekDayConfig).Add(EveryDayEvent);
	}
};
