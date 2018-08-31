// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
// #include "XD_TimeSystemUtility.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(XD_TimeSystem_Log, Log, All);
#define TimeSystem_Display_Log(Format, ...) UE_LOG(XD_TimeSystem_Log, Log, TEXT(Format), ##__VA_ARGS__)
#define TimeSystem_Warning_LOG(Format, ...) UE_LOG(XD_TimeSystem_Log, Warning, TEXT(Format), ##__VA_ARGS__)
#define TimeSystem_Error_Log(Format, ...) UE_LOG(XD_TimeSystem_Log, Error, TEXT(Format), ##__VA_ARGS__)