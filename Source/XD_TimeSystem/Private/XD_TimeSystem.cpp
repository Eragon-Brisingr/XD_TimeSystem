// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "XD_TimeSystem.h"
#if WITH_EDITOR
#include <ISettingsModule.h>
#include <ISettingsSection.h>
#include "XD_TimeSystemSettings.h"
#endif

#define LOCTEXT_NAMESPACE "FXD_TimeSystemModule"

void FXD_TimeSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
	// register settings
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "XD_TimeSystemSettings",
			LOCTEXT("XD_TimeSystemSettings", "XD_TimeSystemSettings"),
			LOCTEXT("XD_TimeSystemSettingsDescription", "Configure the TimeSystemSettings plug-in."),
			GetMutableDefault<UXD_TimeSystemSettings>()
		);
	}
#endif //WITH_EDITOR
}

void FXD_TimeSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXD_TimeSystemModule, XD_TimeSystem)