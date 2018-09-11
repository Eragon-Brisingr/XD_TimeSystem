// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Info.h>
#include "XD_TimeManagerPreview.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, NotBlueprintType, hidecategories = (Input, Movement, Collision, Rendering, "Utilities|Transformation", Actor, HLOD, Tags, LOD, AssetUserData, Cooking), showcategories = ("Input|MouseInput", "Input|TouchInput"))
class XD_TIMESYSTEM_API AXD_TimeManagerPreviewActor : public AInfo
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AXD_TimeManagerPreviewActor();

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }
	virtual void TickActor(float DeltaSeconds, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "时间系统")
	class UXD_TimeManager* PreviewTimeManager;
	
};