﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated, SaveGame, meta = (DisplayName = "当前时间"))
	FXD_GameTime CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated, meta = (DisplayName = "时间流逝倍率"))
	float TimeSpendRate = 20.f;

	//游戏时间事件
public:
	TMap<FXD_EveryHourConfig, TArray<FXD_GameTimeEvent>> EveryHourEvents;

	TMap<FXD_EveryDayConfig, TArray<FXD_GameTimeEvent>> EveryDayEvents;

	TMap<FXD_EveryWeekConfig, TArray<FXD_GameTimeEvent>> EveryWeekDayEvents;

	TMap<FXD_EveryMonthConfig, TArray<FXD_GameTimeEvent>> EveryMonthEvents;

	TMap<FXD_EveryYearConfig, TArray<FXD_GameTimeEvent>> EveryYearEvents;

	TMap<FXD_SpecialTimeConfig, TArray<FXD_GameTimeEvent>> SpecialTimeEvents;

	void InvokeExecuteGameTimeEvents(const TArray<FXD_GameTimeEvent>& GameTimeEvents)
	{
		for (const FXD_GameTimeEvent& GameTimeEvent : GameTimeEvents)
		{
			GameTimeEvent.ExecuteIfBound();
		}
	}

public:
	static UXD_TimeManager* GetGameTimeManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryWeekEvent_Instant(const FXD_EveryWeekConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryYearEvent_Instant(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryWeekDayEvent(const FXD_EveryWeekConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent) const;
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent) const;

public:
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryHourEvent_Duration(const FXD_EveryHourConfig& Start, const FXD_EveryHourConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryDayEvent_Duration(const FXD_EveryDayConfig& Start, const FXD_EveryDayConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryWeekEvent_Duration(const FXD_EveryWeekConfig& Start, const FXD_EveryWeekConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryMonthEvent_Duration(const FXD_EveryMonthConfig& Start, const FXD_EveryMonthConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryYearEvent_Duration(const FXD_EveryYearConfig& Start, const FXD_EveryYearConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddSpecialTimeEvent_Duration(const FXD_SpecialTimeConfig& Start, const FXD_SpecialTimeConfig& End, const FXD_GameTimeEvent& EveryHourEvent);
};