// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "XD_TimeSystem_Editor.h"
#include "XD_GameTime_Customization.h"
#include <PropertyEditorModule.h>
#include "XD_PropertyCustomizationEx.h"

#define LOCTEXT_NAMESPACE "FXD_TimeSystem_EditorModule"

void FXD_TimeSystem_EditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		RegisterCustomProperty(struct FXD_GameTime, FXD_GameTime_Customization);
		RegisterCustomProperty(struct FXD_EveryHourConfig, FXD_EveryHourConfig_Customization);
		RegisterCustomProperty(struct FXD_EveryDayConfig, FXD_EveryDayConfig_Customization);
		RegisterCustomProperty(struct FXD_EveryWeekConfig, FXD_EveryWeekConfig_Customization);
		RegisterCustomProperty(struct FXD_EveryMonthConfig, FXD_EveryMonthConfig_Customization);
		RegisterCustomProperty(struct FXD_EveryYearConfig, FXD_EveryYearConfig_Customization);
		RegisterCustomProperty(struct FXD_SpecialTimeConfig, FXD_SpecialTimeConfig_Customization);
	}
}

void FXD_TimeSystem_EditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXD_TimeSystem_EditorModule, XD_TimeSystem_Editor)