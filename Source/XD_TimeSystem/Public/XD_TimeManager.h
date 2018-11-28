// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XD_SaveGameInterface.h"
#include "XD_TimeSystemType.h"
#include <Engine/LatentActionManager.h>
#include "XD_TimeManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XD_TIMESYSTEM_API UXD_TimeManager : public UActorComponent, public IXD_SaveGameInterface
{
	GENERATED_BODY()

	friend class UXD_TimeManagerFunctionLibrary;
	friend class AXD_TimeManagerPreviewActor;
public:	
	// Sets default values for this component's properties
	UXD_TimeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitTimeEvents();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnRegister() override;

	virtual void OnUnregister() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

public:
	static UXD_TimeManager* GetGameTimeManager(const UObject* WorldContextObject);

#if WITH_EDITOR
	static TWeakObjectPtr<UXD_TimeManager> PreviewTimeManager;
#endif
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated, SaveGame, meta = (DisplayName = "当前时间"))
	FXD_GameTime CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "时间系统", Replicated, meta = (DisplayName = "时间流逝倍率", ClampMin = "0", ClampMax = "1000000"))
	float TimeSpendRate = 20.f;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void SetTimeSpendRate(float Rate) { TimeSpendRate = Rate; }

	static TAutoConsoleVariable<float> CVarTimeSpendRate;
	//游戏时间事件
public:
	TMap<FXD_EveryHourConfig, TArray<FXD_GameTimeEvent>> EveryHourEvents;

	TMap<FXD_EveryDayConfig, TArray<FXD_GameTimeEvent>> EveryDayEvents;

	TMap<FXD_EveryWeekConfig, TArray<FXD_GameTimeEvent>> EveryWeekDayEvents;

	TMap<FXD_EveryMonthConfig, TArray<FXD_GameTimeEvent>> EveryMonthEvents;

	TMap<FXD_EveryYearConfig, TArray<FXD_GameTimeEvent>> EveryYearEvents;

	TMap<FXD_SpecialTimeConfig, TArray<FXD_GameTimeEvent>> SpecialTimeEvents;

	FDelegateHandle OnActorSpawnedHandle;

	void InvokeExecuteGameTimeEvents(const TArray<FXD_GameTimeEvent>& GameTimeEvents)
	{
		for (const FXD_GameTimeEvent& GameTimeEvent : GameTimeEvents)
		{
			GameTimeEvent.ExecuteIfBound();
		}
	}

	//Native版本
public:
	DECLARE_DELEGATE(FXD_GameTimeNativeDelegate);
	TMap<FXD_SpecialTimeConfig, TArray<FXD_GameTimeNativeDelegate>> NativeSpecialTimeEvents;

	FXD_NativeSpecialGameTimeHandle AddNativeSpecialGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate);

	void RemoveNativeSpecialGameTimeEvent(const FXD_NativeSpecialGameTimeHandle& Handle);

	void RemoveNativeSpecialGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const UObject* Object);

	//可被保存的时间事件
public:
	UPROPERTY(SaveGame)
	TMap<FXD_SpecialTimeConfig, FXD_GameTimeEvents> RecordableGameTimeEvents;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddRecordableDelayEvent(const FXD_GameTimeSpan& GameTimeSpan, const FXD_GameTimeEvent& GameTimeEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent);

	//GameTimeDelay
private:
	struct FGameTimeDelayAction
	{
		FGameTimeDelayAction(const FXD_GameTimeSpan& GameTimeSpan, FName ExecutionFunction, int32 OutputLink)
			:TicksRemaining(GameTimeSpan.GetTicks()), ExecutionFunction(ExecutionFunction), OutputLink(OutputLink)
		{}

		int64 TicksRemaining;
		FName ExecutionFunction;
		int32 OutputLink;

		bool operator==(const FGameTimeDelayAction& Action)
		{
			return OutputLink == Action.OutputLink;
		}
	};

	TMap<TWeakObjectPtr<UObject>, TArray<FGameTimeDelayAction>> GameTimeDelayEvents;

	FGameTimeDelayAction* FindDelayEvent(const FLatentActionInfo& LatentInfo);

	bool ContainsDelayEvent(const FLatentActionInfo& LatentInfo);

	void AddDelayEvent(const FXD_GameTimeSpan& GameTimeSpan, const FLatentActionInfo& LatentInfo);
public:
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryHourEvent_Instant(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryDayEvent_Instant(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryWeekEvent_Instant(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryYearEvent_Instant(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& SpecialTimeEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent);
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryWeekDayEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekDayEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& SpecialTimeEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryHourEvent(const FXD_EveryHourConfig& EveryHourConfig, const FXD_GameTimeEvent& EveryHourEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryDayEvent(const FXD_EveryDayConfig& EveryDayConfig, const FXD_GameTimeEvent& EveryDayEvent) const;
	
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryWeekEvent(const FXD_EveryWeekConfig& EveryWeekConfig, const FXD_GameTimeEvent& EveryWeekDayEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryMonthEvent(const FXD_EveryMonthConfig& EveryMonthConfig, const FXD_GameTimeEvent& EveryMonthEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsEveryYearEvent(const FXD_EveryYearConfig& EveryYearConfig, const FXD_GameTimeEvent& EveryYearEvent) const;

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	bool ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& SpecialTimeEvent) const;

public:
	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryHourEvent_Duration(const FXD_EveryHourConfig& Start, const FXD_EveryHourConfig& End, const FXD_GameTimeEvent& EveryHourEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryDayEvent_Duration(const FXD_EveryDayConfig& Start, const FXD_EveryDayConfig& End, const FXD_GameTimeEvent& EveryDayEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryWeekEvent_Duration(const FXD_EveryWeekConfig& Start, const FXD_EveryWeekConfig& End, const FXD_GameTimeEvent& EveryWeekEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryMonthEvent_Duration(const FXD_EveryMonthConfig& Start, const FXD_EveryMonthConfig& End, const FXD_GameTimeEvent& EveryMonthEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddEveryYearEvent_Duration(const FXD_EveryYearConfig& Start, const FXD_EveryYearConfig& End, const FXD_GameTimeEvent& EveryYearEvent);

	UFUNCTION(BlueprintCallable, Category = "游戏|时间系统")
	void AddSpecialTimeEvent_Duration(const FXD_SpecialTimeConfig& Start, const FXD_SpecialTimeConfig& End, const FXD_GameTimeEvent& SpecialTimeEvent);

};
