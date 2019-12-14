// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeManager.h"
#include <Net/UnrealNetwork.h>
#include "XD_TimeSystemUtility.h"
#include "XD_TimeSystem_GameStateInterface.h"
#include <GameFramework/GameStateBase.h>
#include "XD_GameTimeEventInterface.h"
#include <EngineUtils.h>
#include "XD_ActorFunctionLibrary.h"
#include "XD_TimeManagerPreview.h"
#include "XD_TimeSystemSettings.h"


// Sets default values for this component's properties
UXD_TimeManager::UXD_TimeManager()
	:CurrentTime(1000, 1, 1, 0, 0, 0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UXD_TimeManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

	InitTimeEvents();
}


void UXD_TimeManager::InitTimeEvents()
{
#if WITH_EDITOR
	FEditorScriptExecutionGuard ScriptGuard;
#endif
	for (TActorIterator<AActor> It(GetWorld(), AActor::StaticClass()); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor->IsPendingKill())
		{
			IXD_GameTimeEventInterface::InvokeRegisterGameTimeEvent(Actor);
		}
	}
	OnActorSpawnedHandle = GetWorld()->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateLambda([this](AActor* Actor)
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		IXD_GameTimeEventInterface::InvokeRegisterGameTimeEvent(Actor);
	}));
}

void UXD_TimeManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UXD_TimeManager::OnRegister()
{
	Super::OnRegister();

	//GameState在游戏中还没被注册到World中
#if WITH_EDITOR
	if (GetWorld() && GetWorld()->WorldType == EWorldType::Editor)
	{
		PreviewTimeManager = this;
		InitTimeEvents();
	}
#endif
}

void UXD_TimeManager::OnUnregister()
{
	Super::OnUnregister();
	GetWorld()->RemoveOnActorSpawnedHandler(OnActorSpawnedHandle);
}

TAutoConsoleVariable<float> UXD_TimeManager::CVarTimeSpendRate(
	TEXT("Game.Time.SpendRate"),
	20.f,
	TEXT("游戏时间的速度.\n"),
	ECVF_Scalability);

void UXD_TimeManager::InvokeExecuteGameTimeEvents(const TArray<FXD_GameTimeEvent>& GameTimeEvents)
{
	//防止事件执行时删除数组内元素，拷贝一份
	for (const FXD_GameTimeEvent& GameTimeEvent : TArray<FXD_GameTimeEvent>(GameTimeEvents))
	{
		GameTimeEvent.ExecuteIfBound();
	}
}

FXD_NativeSpecialGameTimeHandle UXD_TimeManager::AddNativeSpecialGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate)
{
	FXD_NativeSpecialGameTimeHandle Handle;
	Handle.SpecialTimeConfig = SpecialTimeConfig;
	TArray<FXD_GameTimeNativeDelegate>& Events = NativeSpecialTimeEvents.FindOrAdd(SpecialTimeConfig);
	int32 Index = Events.Add(GameTimeNativeDelegate);
	Handle.DelegateHandle = Events[Index].GetHandle();
	return Handle;
}

FXD_NativeSpecialGameTimeHandle UXD_TimeManager::AddNativeDelayTimeEvent(const FXD_GameTimeSpan& TimeSpan, const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate)
{
	return AddNativeSpecialGameTimeEvent(CurrentTime.ToGameTimeMinuteAccuracy() + FXD_GameTimeSpan(TimeSpan.GetDays(), TimeSpan.GetHours(), TimeSpan.GetMinutes()), GameTimeNativeDelegate);
}

void UXD_TimeManager::RemoveNativeSpecialGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const UObject* Object)
{
	if (TArray<FXD_GameTimeNativeDelegate>* Events = NativeSpecialTimeEvents.Find(SpecialTimeConfig))
	{
		Events->RemoveAll([&](const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate) {return GameTimeNativeDelegate.GetUObject() == Object; });
		if (Events->Num() == 0)
		{
			NativeSpecialTimeEvents.Remove(SpecialTimeConfig);
		}
	}
}

void UXD_TimeManager::RemoveNativeSpecialGameTimeEvent(FXD_NativeSpecialGameTimeHandle& Handle)
{
	if (Handle.DelegateHandle.IsValid())
	{
		if (TArray<FXD_GameTimeNativeDelegate>* Events = NativeSpecialTimeEvents.Find(Handle.SpecialTimeConfig))
		{
			Events->RemoveAll([&](const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate) {return GameTimeNativeDelegate.GetHandle() == Handle.DelegateHandle; });
			if (Events->Num() == 0)
			{
				NativeSpecialTimeEvents.Remove(Handle.SpecialTimeConfig);
			}
		}
	}
}

void UXD_TimeManager::AddRecordableDelayEvent(const FXD_GameTimeSpan& GameTimeSpan, const FXD_GameTimeEvent& GameTimeEvent)
{
	if (GameTimeSpan.GetTicks() >= 0)
	{
		AddRecordableGameTimeEvent(CurrentTime + GameTimeSpan, GameTimeEvent);
	}
	else
	{
		GameTimeEvent.ExecuteIfBound();
	}
}

void UXD_TimeManager::AddRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent)
{
	RecordableGameTimeEvents.FindOrAdd(SpecialTimeConfig).GameTimeEvents.Add(GameTimeEvent);
}

bool UXD_TimeManager::ContainsRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent) const
{
	if (const FXD_GameTimeEvents* Events = RecordableGameTimeEvents.Find(SpecialTimeConfig))
	{
		return Events->GameTimeEvents.Contains(GameTimeEvent);
	}
	return false;
}

void UXD_TimeManager::RemoveRecordableGameTimeEvent(const FXD_SpecialTimeConfig& SpecialTimeConfig, const FXD_GameTimeEvent& GameTimeEvent)
{
	if (FXD_GameTimeEvents* Events = RecordableGameTimeEvents.Find(SpecialTimeConfig))
	{
		Events->GameTimeEvents.Remove(GameTimeEvent);
		if (Events->GameTimeEvents.Num() == 0)
		{
			RecordableGameTimeEvents.Remove(SpecialTimeConfig);
		}
	}
}

#if WITH_EDITOR
void UXD_TimeManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
}
#endif

// Called every frame
void UXD_TimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//GameTimeSpendRate
	if (CVarTimeSpendRate->TestFlags(ECVF_SetByConsole))
	{
		float InvokeRate = CVarTimeSpendRate.GetValueOnGameThread();
		if (InvokeRate != TimeSpendRate)
		{
			SetTimeSpendRate(InvokeRate);
		}
		CVarTimeSpendRate->ClearFlags(ECVF_SetByConsole);
	}

	//GameTimeTick
	int64 PreTicks = CurrentTime.GetTicks();
	CurrentTime += DeltaTime * FXD_GameTimeConfig::TicksPerSecond * TimeSpendRate;

	int64 PreMinutes = PreTicks / FXD_GameTimeConfig::TicksPerMinute;
	int64 CurMinutes = CurrentTime.GetTicks() / FXD_GameTimeConfig::TicksPerMinute;
	int64 SpendMinutes = CurMinutes - PreMinutes;
	if (SpendMinutes > 0)
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		for (FXD_GameTime InterpGameTime((PreMinutes + 1) * FXD_GameTimeConfig::TicksPerMinute); InterpGameTime <= FXD_GameTime(CurMinutes * FXD_GameTimeConfig::TicksPerMinute); InterpGameTime += FXD_GameTimeConfig::TicksPerMinute)
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
				if (TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(FXD_EveryWeekConfig(InterpWeekDay, InterpHour, InterpMinute)))
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
				FXD_SpecialTimeConfig SpecialTimeConfig = FXD_SpecialTimeConfig(InterpYear, InterpMonth, InterpDay, InterpHour, InterpMinute);
				if (TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(SpecialTimeConfig))
				{
					InvokeExecuteGameTimeEvents(*Events);
					//Delete Special Things
					SpecialTimeEvents.Remove(SpecialTimeConfig);
				}

				if (TArray<FXD_GameTimeNativeDelegate>* Events = NativeSpecialTimeEvents.Find(SpecialTimeConfig))
				{
					for (const FXD_GameTimeNativeDelegate& GameTimeNativeDelegate : TArray<FXD_GameTimeNativeDelegate>(*Events))
					{
						GameTimeNativeDelegate.ExecuteIfBound();
					}
					//Delete Special Things
					NativeSpecialTimeEvents.Remove(SpecialTimeConfig);
				}

				if (FXD_GameTimeEvents* Events = RecordableGameTimeEvents.Find(SpecialTimeConfig))
				{
					InvokeExecuteGameTimeEvents(Events->GameTimeEvents);
					//Delete Special Things
					RecordableGameTimeEvents.Remove(SpecialTimeConfig);
				}
			}
		}

		//GameTimeDelay
		TArray<TWeakObjectPtr<UObject>> UnvalidObjects;
		for (TPair<TWeakObjectPtr<UObject>, TArray<FGameTimeDelayAction>>& TargetAndActions : GameTimeDelayEvents)
		{
			TWeakObjectPtr<UObject> CallbackTarget = TargetAndActions.Key;
			TArray<FGameTimeDelayAction>& Actions = TargetAndActions.Value;
			if (CallbackTarget.IsValid())
			{
				TArray<FGameTimeDelayAction> ExecutedActions;
				for (FGameTimeDelayAction& Action : Actions)
				{
					Action.TicksRemaining -= (CurrentTime.GetTicks() - PreTicks);
					if (Action.TicksRemaining <= 0)
					{
						ExecutedActions.Add(Action);
					}
				}

				for (FGameTimeDelayAction& Action : ExecutedActions)
				{
					Actions.Remove(Action);
					//遍历结束后才执行，防止遍历中添加事件改变Actions长度导致迭代器异常
					if (UFunction* TargetFunction = CallbackTarget->FindFunction(Action.ExecutionFunction))
					{
						CallbackTarget->ProcessEvent(TargetFunction, &(Action.OutputLink));
					}
				}

				if (ExecutedActions.Num() == GameTimeDelayEvents.Num())
				{
					UnvalidObjects.Add(CallbackTarget);
				}
			}
			else
			{
				UnvalidObjects.Add(CallbackTarget);
			}
		}

		for (TWeakObjectPtr<UObject>& NeedRemoveObject : UnvalidObjects)
		{
			GameTimeDelayEvents.Remove(NeedRemoveObject);
		}
	}
}

void UXD_TimeManager::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXD_TimeManager, CurrentTime, COND_InitialOnly);
	DOREPLIFETIME(UXD_TimeManager, TimeSpendRate);
}

#if WITH_EDITOR
TWeakObjectPtr<UXD_TimeManager> UXD_TimeManager::PreviewTimeManager;
#endif

UXD_TimeManager::FGameTimeDelayAction* UXD_TimeManager::FindDelayEvent(const FLatentActionInfo& LatentInfo)
{
	if (TArray<FGameTimeDelayAction>* Actions = GameTimeDelayEvents.Find(LatentInfo.CallbackTarget))
	{
		return Actions->FindByPredicate([&](const FGameTimeDelayAction& E) {return E.OutputLink == LatentInfo.Linkage; });
	}
	return nullptr;
}

bool UXD_TimeManager::ContainsDelayEvent(const FLatentActionInfo& LatentInfo)
{
	return FindDelayEvent(LatentInfo) != nullptr;
}

void UXD_TimeManager::AddDelayEvent(const FXD_GameTimeSpan& GameTimeSpan, const FLatentActionInfo& LatentInfo)
{
	GameTimeDelayEvents.FindOrAdd(LatentInfo.CallbackTarget).Add(FGameTimeDelayAction(GameTimeSpan, LatentInfo.ExecutionFunction, LatentInfo.Linkage));
}

UXD_TimeManager* UXD_TimeManager::GetGameTimeManager(const UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();
#if WITH_EDITOR
	if (World == nullptr)
	{
		return nullptr;
	}
	if (World->WorldType == EWorldType::Editor)
	{
		if (PreviewTimeManager.IsValid())
		{
			return PreviewTimeManager.Get();
		}
		else if (TActorIterator<AXD_TimeManagerPreviewActor> It = TActorIterator<AXD_TimeManagerPreviewActor>(World, GetDefault<UXD_TimeSystemSettings>()->TimeManagerPreviewActorClass))
		{
			AXD_TimeManagerPreviewActor* TimeManagerPreviewActor = *It;
			PreviewTimeManager = TimeManagerPreviewActor->PreviewTimeManager;
			return TimeManagerPreviewActor->PreviewTimeManager;
		}
		else if (TSubclassOf<AXD_TimeManagerPreviewActor> TimeManagerPreviewActorClass = GetDefault<UXD_TimeSystemSettings>()->TimeManagerPreviewActorClass)
		{
			return World->SpawnActor<AXD_TimeManagerPreviewActor>(TimeManagerPreviewActorClass)->PreviewTimeManager;
		}
		return nullptr;
	}
#endif
	if (AGameStateBase* GameState = World->GetGameState())
	{
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
		return UXD_ActorFunctionLibrary::AddComponent<UXD_TimeManager>(GameState, TEXT("临时时间系统"));
	}
	return nullptr;
}

void UXD_TimeManager::AddEveryHourEvent_Instant(const FXD_EveryHourConfig& Date, const FXD_GameTimeEvent& EveryHourEvent)
{
	EveryHourEvents.FindOrAdd(Date).Add(EveryHourEvent);
}

void UXD_TimeManager::AddEveryDayEvent_Instant(const FXD_EveryDayConfig& Date, const FXD_GameTimeEvent& EveryDayEvent)
{
	EveryDayEvents.FindOrAdd(Date).Add(EveryDayEvent);
}

void UXD_TimeManager::AddEveryWeekEvent_Instant(const FXD_EveryWeekConfig& Date, const FXD_GameTimeEvent& EveryWeekDayEvent)
{
	EveryWeekDayEvents.FindOrAdd(Date).Add(EveryWeekDayEvent);
}

void UXD_TimeManager::AddEveryMonthEvent_Instant(const FXD_EveryMonthConfig& Date, const FXD_GameTimeEvent& EveryMonthEvent)
{
	EveryMonthEvents.FindOrAdd(Date).Add(EveryMonthEvent);
}

void UXD_TimeManager::AddEveryYearEvent_Instant(const FXD_EveryYearConfig& Date, const FXD_GameTimeEvent& EveryYearEvent)
{
	EveryYearEvents.FindOrAdd(Date).Add(EveryYearEvent);
}

void UXD_TimeManager::AddSpecialTimeEvent_Instant(const FXD_SpecialTimeConfig& Date, const FXD_GameTimeEvent& SpecialTimeEvent)
{
	SpecialTimeEvents.FindOrAdd(Date).Add(SpecialTimeEvent);
}

void UXD_TimeManager::RemoveEveryHourEvent(const FXD_EveryHourConfig& Date, const FXD_GameTimeEvent& EveryHourEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(Date))
	{
		Events->RemoveSingle(EveryHourEvent);
		if (Events->Num() == 0)
		{
			EveryHourEvents.Remove(Date);
		}
	}
}

void UXD_TimeManager::RemoveEveryDayEvent(const FXD_EveryDayConfig& Date, const FXD_GameTimeEvent& EveryDayEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(Date))
	{
		Events->RemoveSingle(EveryDayEvent);
		if (Events->Num() == 0)
		{
			EveryDayEvents.Remove(Date);
		}
	}
}

void UXD_TimeManager::RemoveEveryWeekEvent(const FXD_EveryWeekConfig& Date, const FXD_GameTimeEvent& EveryWeekDayEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(Date))
	{
		Events->RemoveSingle(EveryWeekDayEvent);
		if (Events->Num() == 0)
		{
			EveryWeekDayEvents.Remove(Date);
		}
	}
}

void UXD_TimeManager::RemoveEveryMonthEvent(const FXD_EveryMonthConfig& Date, const FXD_GameTimeEvent& EveryMonthEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(Date))
	{
		Events->RemoveSingle(EveryMonthEvent);
		if (Events->Num() == 0)
		{
			EveryMonthEvents.Remove(Date);
		}
	}
}

void UXD_TimeManager::RemoveEveryYearEvent(const FXD_EveryYearConfig& Date, const FXD_GameTimeEvent& EveryYearEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = EveryYearEvents.Find(Date))
	{
		Events->RemoveSingle(EveryYearEvent);
		if (Events->Num() == 0)
		{
			EveryYearEvents.Remove(Date);
		}
	}
}

void UXD_TimeManager::RemoveSpecialTimeEvent(const FXD_SpecialTimeConfig& Date, const FXD_GameTimeEvent& SpecialTimeEvent)
{
	if (TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(Date))
	{
		Events->RemoveSingle(SpecialTimeEvent);
		if (Events->Num() == 0)
		{
			SpecialTimeEvents.Remove(Date);
		}
	}
}

bool UXD_TimeManager::ContainsEveryHourEvent(const FXD_EveryHourConfig& Date, const FXD_GameTimeEvent& EveryHourEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryHourEvents.Find(Date))
	{
		return Events->Contains(EveryHourEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryDayEvent(const FXD_EveryDayConfig& Date, const FXD_GameTimeEvent& EveryDayEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryDayEvents.Find(Date))
	{
		return Events->Contains(EveryDayEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryWeekEvent(const FXD_EveryWeekConfig& Date, const FXD_GameTimeEvent& EveryWeekDayEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryWeekDayEvents.Find(Date))
	{
		return Events->Contains(EveryWeekDayEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryMonthEvent(const FXD_EveryMonthConfig& Date, const FXD_GameTimeEvent& EveryMonthEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryMonthEvents.Find(Date))
	{
		return Events->Contains(EveryMonthEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsEveryYearEvent(const FXD_EveryYearConfig& Date, const FXD_GameTimeEvent& EveryYearEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = EveryYearEvents.Find(Date))
	{
		return Events->Contains(EveryYearEvent);
	}
	return false;
}

bool UXD_TimeManager::ContainsSpecialTimeEvent(const FXD_SpecialTimeConfig& Date, const FXD_GameTimeEvent& SpecialTimeEvent) const
{
	if (const TArray<FXD_GameTimeEvent>* Events = SpecialTimeEvents.Find(Date))
	{
		return Events->Contains(SpecialTimeEvent);
	}
	return false;
}

void UXD_TimeManager::AddEveryHourEvent_Duration(const FXD_EveryHourConfig& Start, const FXD_EveryHourConfig& End, const FXD_GameTimeEvent& EveryHourEvent)
{
	if (CurrentTime.InHourRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		EveryHourEvent.ExecuteIfBound();
	}
	AddEveryHourEvent_Instant(Start, EveryHourEvent);
}

void UXD_TimeManager::AddEveryDayEvent_Duration(const FXD_EveryDayConfig& Start, const FXD_EveryDayConfig& End, const FXD_GameTimeEvent& EveryDayEvent)
{
	if (CurrentTime.InDayRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		EveryDayEvent.ExecuteIfBound();
	}
	AddEveryDayEvent_Instant(Start, EveryDayEvent);
}

void UXD_TimeManager::AddEveryWeekEvent_Duration(const FXD_EveryWeekConfig& Start, const FXD_EveryWeekConfig& End, const FXD_GameTimeEvent& EveryWeekEvent)
{
	if (CurrentTime.InWeekRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		EveryWeekEvent.ExecuteIfBound();
	}
	AddEveryWeekEvent_Instant(Start, EveryWeekEvent);
}

void UXD_TimeManager::AddEveryMonthEvent_Duration(const FXD_EveryMonthConfig& Start, const FXD_EveryMonthConfig& End, const FXD_GameTimeEvent& EveryMonthEvent)
{
	if (CurrentTime.InMonthRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		EveryMonthEvent.ExecuteIfBound();
	}
	AddEveryMonthEvent_Instant(Start, EveryMonthEvent);
}

void UXD_TimeManager::AddEveryYearEvent_Duration(const FXD_EveryYearConfig& Start, const FXD_EveryYearConfig& End, const FXD_GameTimeEvent& EveryYearEvent)
{
	if (CurrentTime.InYearRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		EveryYearEvent.ExecuteIfBound();
	}
	AddEveryYearEvent_Instant(Start, EveryYearEvent);
}

void UXD_TimeManager::AddSpecialTimeEvent_Duration(const FXD_SpecialTimeConfig& Start, const FXD_SpecialTimeConfig& End, const FXD_GameTimeEvent& SpecialTimeEvent)
{
	if (CurrentTime.InSpecialTimeRange(Start, End))
	{
#if WITH_EDITOR
		FEditorScriptExecutionGuard ScriptGuard;
#endif
		SpecialTimeEvent.ExecuteIfBound();
	}
	else if (CurrentTime.GetTicks() < Start.GetTicks())
	{
		AddSpecialTimeEvent_Instant(Start, SpecialTimeEvent);
	}
}
