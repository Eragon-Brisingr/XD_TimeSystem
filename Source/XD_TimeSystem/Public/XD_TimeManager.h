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

	TMap<int32, TArray<FXD_GameTimeTask>> EveryMinuteEvent;

	TMap<int32, TArray<FXD_GameTimeTask>> EveryHourEvent;

	TMap<int32, TArray<FXD_GameTimeTask>> EveryDayEvent;


};
