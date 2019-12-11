// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include <UObject/NoExportTypes.h>
// #include "XD_TimeSystem_EditorUtility.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(XD_TimeSystem_Editor_Log, Log, All);
#define TimeSystem_Editor_Display_Log(Format, ...) UE_LOG(XD_TimeSystem_Editor_Log, Log, TEXT(Format), ##__VA_ARGS__)
#define TimeSystem_Editor_Warning_LOG(Format, ...) UE_LOG(XD_TimeSystem_Editor_Log, Warning, TEXT(Format), ##__VA_ARGS__)
#define TimeSystem_Editor_Error_Log(Format, ...) UE_LOG(XD_TimeSystem_Editor_Log, Error, TEXT(Format), ##__VA_ARGS__)