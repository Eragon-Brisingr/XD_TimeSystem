// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeManagerPreview.h"
#include "XD_TimeManager.h"

AXD_TimeManagerPreviewActor::AXD_TimeManagerPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsEditorOnlyActor = true;

	PreviewTimeManager = CreateDefaultSubobject<UXD_TimeManager>(GET_MEMBER_NAME_CHECKED(AXD_TimeManagerPreviewActor, PreviewTimeManager));
}

#if WITH_EDITOR
void AXD_TimeManagerPreviewActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif // WITH_EDITOR

void AXD_TimeManagerPreviewActor::TickActor(float DeltaSeconds, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	FEditorScriptExecutionGuard ScriptGuard;
	Super::TickActor(DeltaSeconds, TickType, ThisTickFunction);
}

void AXD_TimeManagerPreviewActor::Tick(float DeltaTime)
{
	if (GetWorld()->WorldType == EWorldType::Editor)
	{
		Super::Tick(DeltaTime);
	}
}

void AXD_TimeManagerPreviewActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (GetWorld()->WorldType == EWorldType::Editor)
	{
#if WITH_EDITOR
		UXD_TimeManager::PreviewTimeManager = PreviewTimeManager;
#endif
	}
}

