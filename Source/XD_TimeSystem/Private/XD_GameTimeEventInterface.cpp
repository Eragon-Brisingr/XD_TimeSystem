// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_GameTimeEventInterface.h"
#include <GameFramework/Actor.h>


// Add default functionality here for any IXD_GameTimeEventInterface functions that are not pure virtual.

void IXD_GameTimeEventInterface::InvokeConfigGameTimeEvent(class AActor* Actor)
{
	if (Actor->Implements<UXD_GameTimeEventInterface>())
	{
		IXD_GameTimeEventInterface::Execute_ConfigGameTimeEvent(Actor);
	}
}
