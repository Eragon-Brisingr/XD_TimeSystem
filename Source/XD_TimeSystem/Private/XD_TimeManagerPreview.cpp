// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_TimeManagerPreview.h"
#include "XD_TimeManager.h"

AXD_TimeManagerPreviewActor::AXD_TimeManagerPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsEditorOnlyActor = true;

	PreviewTimeManager = CreateDefaultSubobject<UXD_TimeManager>(GET_MEMBER_NAME_CHECKED(AXD_TimeManagerPreviewActor, PreviewTimeManager));
}

void AXD_TimeManagerPreviewActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (AActor* AttachedActor : AttachedActors)
	{
		AttachedActor->Destroy();
	}
	Destroy();
}

#if WITH_EDITOR
void AXD_TimeManagerPreviewActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

bool AXD_TimeManagerPreviewActor::ShouldTickIfViewportsOnly() const
{
	if (UWorld* World = GetWorld())
	{
		return World->WorldType == EWorldType::Editor && !Pause;
	}
	return false;
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
}

