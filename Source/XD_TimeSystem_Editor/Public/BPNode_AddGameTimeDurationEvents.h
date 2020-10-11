// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "BPNode_AddGameTimeDurationEvents.generated.h"

/**
 * 
 */
UCLASS(abstract)
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddGameTimeDurationEvents : public UK2Node
{
	GENERATED_BODY()
public:
 	// UEdGraphNode interface
 	void AllocateDefaultPins() override;
 
 	// UK2Node interface
 	void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;
 	void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;
	void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

 	FName GetCornerIcon() const override { return TEXT("Graph.Latent.LatentIcon"); }
 	FText GetMenuCategory() const override;
 	// End of UK2Node interface
	
public:
	UPROPERTY()
	int32 EventsNumber = 2;
	
	UPROPERTY(Transient)
	UFunction* AddGameTimeDurationEventsFunction;
	UPROPERTY(Transient)
	UFunction* RemoveGameTimeDurationEventsFunction;

	UPROPERTY(Transient)
	class UStruct* GameTimeConfigType;

protected:
	FText MakeTimeNodeTitle(ENodeTitleType::Type TitleType, const FText& Title) const;
private:
	void AddEvent();
	void RemoveEvent();

	FName GetStartPinName(int32 Idx);
	FName GetEventPinName(int32 Idx);

	static FName BindPinName;
	static FName UnbindPinName;
	static FName IsBindPinName;
	static FString EventName;

	static FString StartParamName;
	static FString EndParamName;
	static FString EventParamName;
};

UCLASS(meta = (DisplayName = "每时循环事件"))
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryHourCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryHourCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS(meta = (DisplayName = "每日循环事件"))
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryDayCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryDayCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS(meta = (DisplayName = "每周循环事件"))
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryWeekCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryWeekCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS(meta = (DisplayName = "每月循环事件"))
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryMonthCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryMonthCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS(meta = (DisplayName = "每年循环事件"))
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryYearCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryYearCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

