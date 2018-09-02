// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "BPNode_AddGameTimeDurationEvents.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddGameTimeDurationEvents : public UK2Node
{
	GENERATED_BODY()
public:
 	// UEdGraphNode interface
 	virtual void AllocateDefaultPins() override;
 	//virtual void PostLoad() override;
 	//virtual void PostReconstructNode() override;
 	//节点名
 	//virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
 	//virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;
 	//virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
 	// End of UEdGraphNode interface
 
 	// UK2Node interface
 	//重写该函数向编辑器注册该节点。
 	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;
 	//展开节点[连接里面的多个蓝图节点]
 	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
 
 	//右键菜单发生的事
 	virtual void GetContextMenuActions(const FGraphNodeContextMenuBuilder& Context) const override;
 	//报错
 	//virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;
 	virtual FName GetCornerIcon() const { return TEXT("Graph.Latent.LatentIcon"); }
 	virtual FText GetMenuCategory() const override;
 	//virtual FText GetTooltipText() const override;
 	//virtual FText GetKeywords() const override;
 	// End of UK2Node interface
	
public:
	UPROPERTY()
	int32 EventsNumber = 2;
	
	UPROPERTY(Transient)
	UFunction* AddGameTimeDurationEventsFunction;

	UPROPERTY(Transient)
	class UStruct* GameTimeConfigType;

	FString EventParamName = TEXT("Event");
private:
	void AddEvent(UEdGraphPin* Pin);

	void RemoveEvent(UEdGraphPin* Pin);

	void AddEvent_Impl(int32 Idx);

	TArray<UEdGraphPin*> StartPins;
	TArray<UEdGraphPin*> EventPins;
};

UCLASS()
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryHourCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryHourCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};


UCLASS()
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryDayCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryDayCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS()
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryWeekCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryWeekCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS()
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryMonthCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryMonthCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

UCLASS()
class XD_TIMESYSTEM_EDITOR_API UBPNode_AddEveryYearCircleEvents : public UBPNode_AddGameTimeDurationEvents
{
	GENERATED_BODY()
public:
	UBPNode_AddEveryYearCircleEvents();

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};

