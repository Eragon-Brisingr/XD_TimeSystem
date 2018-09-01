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

	TMap<FXD_EveryWeekDayConfig, TArray<FXD_GameTimeEvent>> EveryWeekDayEvents;

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
	void AddEveryWeekDayEvent_Instant(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

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
	void RemoveEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

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
	bool ContainsEveryWeekDayEvent(const FXD_EveryWeekDayConfig& EveryWeekDayConfig, const FXD_GameTimeEvent& EveryWeekDayEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& EveryYearEvent) const;
public:
};
