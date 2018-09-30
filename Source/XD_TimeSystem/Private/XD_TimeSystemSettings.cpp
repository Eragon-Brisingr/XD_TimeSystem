// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeSystemSettings.h"
#include "XD_TimeManagerPreview.h"




UXD_TimeSystemSettings::UXD_TimeSystemSettings()
{
#if WITH_EDITOR
	TimeManagerPreviewActorClass = AXD_TimeManagerPreviewActor::StaticClass();
#endif
}
