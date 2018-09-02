// Fill out your copyright notice in the Description page of Project Settings.

#include "BPNode_AddGameTimeDurationEvents.h"
#include <EdGraph/EdGraphNode.h>
#include <EdGraphSchema_K2.h>
#include <BlueprintActionDatabaseRegistrar.h>
#include <BlueprintNodeSpawner.h>
#include "XD_TimeSystemFunctionLibrary.h"
#include "XD_TimeSystemType.h"
#include <BlueprintEditorUtils.h>
#include <K2Node_CallFunction.h>
#include <K2Node_CustomEvent.h>
#include <KismetCompiler.h>
#include "XD_TimeSystem_EditorUtility.h"
#include <K2Node_Knot.h>

#define LOCTEXT_NAMESPACE "TimeSystem_Editor"

const FString StartParamName = TEXT("Start");
const FString EndParamName = TEXT("End");
const FString EventName = TEXT("Event");

const FName GetStartPinName(int32 Idx)
{
	return *FString::Printf(TEXT("[%d]%s"), Idx, *StartParamName);
}

const FName GetEventPinName(int32 Idx)
{
	return *FString::Printf(TEXT("[%d]%s"), Idx, *EventName);
}

void UBPNode_AddGameTimeDurationEvents::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, NAME_None, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NAME_None, UEdGraphSchema_K2::PN_Then);

	for (int i = 1; i <= EventsNumber; ++i)
	{
		AddEvent_Impl(i);
	}
}

void UBPNode_AddGameTimeDurationEvents::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	if (AddGameTimeDurationEventsFunction && GameTimeConfigType)
	{
		UClass* ActionKey = GetClass();
		if (ActionRegistrar.IsOpenForRegistration(ActionKey))
		{
			UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
			check(NodeSpawner != nullptr);

			ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
		}
	}
}

void UBPNode_AddGameTimeDurationEvents::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	UEdGraphPin* PreThenPin = nullptr;

	TArray<UK2Node_CallFunction*> AddTimeEventFunctions;
	for (int32 Idx = 1; Idx <= EventsNumber; ++Idx)
	{
		//函数
		UK2Node_CallFunction* AddTimeEventFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		AddTimeEventFunction->SetFromFunction(AddGameTimeDurationEventsFunction);
		AddTimeEventFunction->AllocateDefaultPins();
		AddTimeEventFunctions.Add(AddTimeEventFunction);

		//创建委托
		UK2Node_CustomEvent* TimeEvent = CompilerContext.SpawnIntermediateEventNode<UK2Node_CustomEvent>(this, AddTimeEventFunction->FindPinChecked(EventParamName), SourceGraph);
		TimeEvent->CustomFunctionName = *FString::Printf(TEXT("%s_[%s]_[%d]"), *GetNodeTitle(ENodeTitleType::FullTitle).ToString(), *CompilerContext.GetGuid(this), Idx + 1);
		TimeEvent->AllocateDefaultPins();

		TimeEvent->FindPinChecked(UK2Node_CustomEvent::DelegateOutputName)->MakeLinkTo(AddTimeEventFunction->FindPinChecked(EventParamName));
		
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(GetEventPinName(Idx)), *CompilerContext.GetSchema()->FindExecutionPin(*TimeEvent, EGPD_Output));

		if (Idx == 1)
		{
			CompilerContext.MovePinLinksToIntermediate(*GetExecPin(), *AddTimeEventFunction->GetExecPin());
		}
		else
		{
			PreThenPin->MakeLinkTo(AddTimeEventFunction->GetExecPin());
		}
		PreThenPin = AddTimeEventFunction->GetThenPin();
	}
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(UEdGraphSchema_K2::PN_Then), *PreThenPin);

	TArray<UK2Node_Knot*> StartTimePins;
	for (int32 Idx = 1; Idx <= EventsNumber; ++Idx)
	{
		UK2Node_Knot* RerouteNode = CompilerContext.SpawnIntermediateNode<UK2Node_Knot>(this, SourceGraph);
		RerouteNode->AllocateDefaultPins();
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(GetStartPinName(Idx)), *RerouteNode->GetInputPin());
		StartTimePins.Add(RerouteNode);
	}

	for (int32 Idx = 0; Idx < EventsNumber; ++Idx)
	{
		if (Idx == 0)
		{
			StartTimePins[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[EventsNumber - 1]->FindPinChecked(EndParamName));
		}
		else
		{
			StartTimePins[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[Idx - 1]->FindPinChecked(EndParamName));
		}
		StartTimePins[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[Idx]->FindPinChecked(StartParamName));
	}
}

void UBPNode_AddGameTimeDurationEvents::GetContextMenuActions(const FGraphNodeContextMenuBuilder& Context) const
{
	Super::GetContextMenuActions(Context);

	if (!Context.bIsDebugging)
	{
		Context.MenuBuilder->BeginSection(NAME_None, LOCTEXT("时间系统", "时间系统"));

		if (Context.Pin != NULL)
		{
			// we only do this for normal BlendList/BlendList by enum, BlendList by Bool doesn't support add/remove pins
			if (Context.Pin->Direction == EGPD_Output && EventsNumber > 2 && Context.Pin->GetDisplayName().ToString().Contains(EventName))
			{
				Context.MenuBuilder->AddMenuEntry(
					LOCTEXT("移除该事件", "移除该事件"),
					LOCTEXT("移除该事件", "移除该事件"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(this, &UBPNode_AddGameTimeDurationEvents::RemoveEvent, const_cast<UEdGraphPin*>(Context.Pin))
					)
				);
			}
		}
		Context.MenuBuilder->AddMenuEntry(
			LOCTEXT("增加时间事件", "增加时间事件"),
			LOCTEXT("增加时间事件", "增加时间事件"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateUObject(this, &UBPNode_AddGameTimeDurationEvents::AddEvent, const_cast<UEdGraphPin*>(Context.Pin))
			)
		);

		Context.MenuBuilder->EndSection();
	}
}

FText UBPNode_AddGameTimeDurationEvents::GetMenuCategory() const
{
	return LOCTEXT("游戏|时间系统", "游戏|时间系统");
}

void UBPNode_AddGameTimeDurationEvents::AddEvent(UEdGraphPin* Pin)
{
	Modify();

	EventsNumber += 1;
	AddEvent_Impl(EventsNumber);

	const bool bIsCompiling = GetBlueprint()->bBeingCompiled;
	if (!bIsCompiling)
	{
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}

void UBPNode_AddGameTimeDurationEvents::AddEvent_Impl(int32 Idx)
{
	FCreatePinParams InTextPinCreatePinParams;
	InTextPinCreatePinParams.bIsReference = true;
	InTextPinCreatePinParams.bIsConst = true;

	StartPins.Add(CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, GameTimeConfigType, GetStartPinName(Idx), InTextPinCreatePinParams));

	EventPins.Add(CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, NULL, GetEventPinName(Idx)));
}

void UBPNode_AddGameTimeDurationEvents::RemoveEvent(UEdGraphPin* Pin)
{
	Modify();

	int32 Idx = EventPins.IndexOfByPredicate([&](UEdGraphPin* E) {return E == Pin; });
	if (Idx != INDEX_NONE)
	{
		EventsNumber -= 1;

		RemovePin(StartPins[Idx]);
		RemovePin(EventPins[Idx]);
		StartPins.RemoveAt(Idx);
		EventPins.RemoveAt(Idx);
	}

	const bool bIsCompiling = GetBlueprint()->bBeingCompiled;
	if (!bIsCompiling)
	{
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}
}

UBPNode_AddEveryHourCircleEvents::UBPNode_AddEveryHourCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryHourEvent_Duration));
	GameTimeConfigType = FXD_EveryHourConfig::StaticStruct();
}

FText UBPNode_AddEveryHourCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Add Every Hour Circle Events", "Add Every Hour Circle Events");
}

UBPNode_AddEveryDayCircleEvents::UBPNode_AddEveryDayCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryDayEvent_Duration));
	GameTimeConfigType = FXD_EveryDayConfig::StaticStruct();
}

FText UBPNode_AddEveryDayCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Add Every Day Circle Events", "Add Every Day Circle Events");
}

UBPNode_AddEveryWeekCircleEvents::UBPNode_AddEveryWeekCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryWeekEvent_Duration));
	GameTimeConfigType = FXD_EveryWeekConfig::StaticStruct();
}

FText UBPNode_AddEveryWeekCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Add Every Week Circle Events", "Add Every Week Circle Events");
}

UBPNode_AddEveryMonthCircleEvents::UBPNode_AddEveryMonthCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryMonthEvent_Duration));
	GameTimeConfigType = FXD_EveryMonthConfig::StaticStruct();
}

FText UBPNode_AddEveryMonthCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Add Every Month Circle Events", "Add Every Month Circle Events");
}

UBPNode_AddEveryYearCircleEvents::UBPNode_AddEveryYearCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryYearEvent_Duration));
	GameTimeConfigType = FXD_EveryYearConfig::StaticStruct();
}

FText UBPNode_AddEveryYearCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("Add Every Year Circle Events", "Add Every Year Circle Events");
}

#undef LOCTEXT_NAMESPACE
