// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/NoExportTypes.h>
#include "XD_TimeSystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = "XD_TimeSystemSetting", defaultconfig)
class XD_TIMESYSTEM_API UXD_TimeSystemSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UXD_TimeSystemSettings();
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "时间系统", Config)
	TSubclassOf<class AXD_TimeManagerPreviewActor> TimeManagerPreviewActorClass;
#endif
};
