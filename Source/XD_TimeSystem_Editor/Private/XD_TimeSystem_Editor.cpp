// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "XD_TimeSystem_Editor.h"
#include "XD_GameTime_Customization.h"
#include <PropertyEditorModule.h>

#define LOCTEXT_NAMESPACE "FXD_TimeSystem_EditorModule"

void FXD_TimeSystem_EditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_GameTime"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_GameTime_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_EveryHourConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_EveryHourConfig_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_EveryDayConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_EveryDayConfig_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_EveryWeekConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_EveryWeekConfig_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_EveryMonthConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_EveryMonthConfig_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_EveryYearConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_EveryYearConfig_Customization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout(TEXT("XD_SpecialTimeConfig"), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FXD_SpecialTimeConfig_Customization::MakeInstance));
	}
}

void FXD_TimeSystem_EditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (FPropertyEditorModule* PropertyModulePtr = FModuleManager::LoadModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = *PropertyModulePtr;

		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_GameTime"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_EveryHourConfig"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_EveryDayConfig"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_EveryWeekConfig"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_EveryMonthConfig"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_EveryYearConfig"));
		PropertyModule.UnregisterCustomPropertyTypeLayout(TEXT("XD_SpecialTimeConfig"));
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXD_TimeSystem_EditorModule, XD_TimeSystem_Editor)