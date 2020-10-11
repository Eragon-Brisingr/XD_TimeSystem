// Fill out your copyright notice in the Description page of Project Settings.

#include "BPNode_AddGameTimeDurationEvents.h"
#include <EdGraph/EdGraphNode.h>
#include <EdGraphSchema_K2.h>
#include <BlueprintActionDatabaseRegistrar.h>
#include <BlueprintNodeSpawner.h>
#include <Kismet2/BlueprintEditorUtils.h>
#include <KismetCompiler.h>
#include <ToolMenu.h>
#include <ToolMenuSection.h>
#include <K2Node_CallFunction.h>
#include <K2Node_CustomEvent.h>
#include <K2Node_Knot.h>
#include <K2Node_TemporaryVariable.h>
#include <K2Node_IfThenElse.h>
#include <K2Node_AssignmentStatement.h>

#include "XD_TimeSystemFunctionLibrary.h"
#include "XD_TimeSystemType.h"
#include "XD_TimeSystem_EditorUtility.h"

#define LOCTEXT_NAMESPACE "TimeSystem_Editor"

FName UBPNode_AddGameTimeDurationEvents::BindPinName = TEXT("激活时间事件绑定");
FName UBPNode_AddGameTimeDurationEvents::UnbindPinName = TEXT("取消时间事件绑定");
FName UBPNode_AddGameTimeDurationEvents::IsBindPinName = TEXT("IsActived");

FString UBPNode_AddGameTimeDurationEvents::EventName = TEXT("事件");
FString UBPNode_AddGameTimeDurationEvents::StartParamName = TEXT("Start");
FString UBPNode_AddGameTimeDurationEvents::EndParamName = TEXT("End");
FString UBPNode_AddGameTimeDurationEvents::EventParamName = TEXT("Event");

FName UBPNode_AddGameTimeDurationEvents::GetStartPinName(int32 Idx)
{
	return *FString::Printf(TEXT("事件[%d]开始时间"), Idx);
}

FName UBPNode_AddGameTimeDurationEvents::GetEventPinName(int32 Idx)
{
	return *FString::Printf(TEXT("事件[%d]"), Idx, *EventName);
}

void UBPNode_AddGameTimeDurationEvents::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, NAME_None, BindPinName);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, NAME_None, UnbindPinName);

	for (int32 Idx = 1; Idx <= EventsNumber; ++Idx)
	{
		FCreatePinParams InTextPinCreatePinParams;
		InTextPinCreatePinParams.bIsReference = true;
		InTextPinCreatePinParams.bIsConst = true;

		CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, GameTimeConfigType, GetStartPinName(Idx), InTextPinCreatePinParams);
		CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, nullptr, GetEventPinName(Idx));
	}
	
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Boolean, NAME_None, IsBindPinName);
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
	check(AddGameTimeDurationEventsFunction && RemoveGameTimeDurationEventsFunction);

	UK2Node_TemporaryVariable* DoOnceVar = CompilerContext.SpawnIntermediateNode<UK2Node_TemporaryVariable>(this, SourceGraph);
	DoOnceVar->VariableType = FEdGraphPinType(UEdGraphSchema_K2::PC_Boolean, NAME_None, nullptr, EPinContainerType::None, false, FEdGraphTerminalType());
	DoOnceVar->bIsPersistent = false;
	DoOnceVar->AllocateDefaultPins();
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(IsBindPinName), *DoOnceVar->GetVariablePin());

	UEdGraphPin* PreBindEventThenPin = nullptr;
	UK2Node_IfThenElse* BindEventIfThenElse = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	BindEventIfThenElse->AllocateDefaultPins();
	BindEventIfThenElse->GetConditionPin()->MakeLinkTo(DoOnceVar->GetVariablePin());

	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(BindPinName), *BindEventIfThenElse->GetExecPin());
	PreBindEventThenPin = BindEventIfThenElse->GetElsePin();

	UK2Node_AssignmentStatement* BindEventAssignment = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);
	BindEventAssignment->AllocateDefaultPins();
	BindEventAssignment->GetVariablePin()->MakeLinkTo(DoOnceVar->GetVariablePin());
	BindEventAssignment->PostReconstructNode();
	BindEventAssignment->GetValuePin()->DefaultValue = TEXT("true");
	PreBindEventThenPin->MakeLinkTo(BindEventAssignment->GetExecPin());
	PreBindEventThenPin = BindEventAssignment->GetThenPin();

	TArray<UK2Node_CustomEvent*> TimeEvents;
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
		TimeEvent->CustomFunctionName = *FString::Printf(TEXT("%s_%s_%d"), *GetNodeTitle(ENodeTitleType::FullTitle).ToString(), *CompilerContext.GetGuid(this), Idx + 1);
		TimeEvent->AllocateDefaultPins();
		TimeEvents.Add(TimeEvent);

		TimeEvent->FindPinChecked(UK2Node_CustomEvent::DelegateOutputName)->MakeLinkTo(AddTimeEventFunction->FindPinChecked(EventParamName));
		
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(GetEventPinName(Idx)), *CompilerContext.GetSchema()->FindExecutionPin(*TimeEvent, EGPD_Output));

		PreBindEventThenPin->MakeLinkTo(AddTimeEventFunction->GetExecPin());
		PreBindEventThenPin = AddTimeEventFunction->GetThenPin();
	}

	TArray<UK2Node_Knot*> StartTimeKnots;
	for (int32 Idx = 1; Idx <= EventsNumber; ++Idx)
	{
		UK2Node_Knot* RerouteNode = CompilerContext.SpawnIntermediateNode<UK2Node_Knot>(this, SourceGraph);
		RerouteNode->AllocateDefaultPins();
		CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(GetStartPinName(Idx)), *RerouteNode->GetInputPin());
		StartTimeKnots.Add(RerouteNode);
	}
	for (int32 Idx = 0; Idx < EventsNumber; ++Idx)
	{
		if (Idx == 0)
		{
			StartTimeKnots[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[EventsNumber - 1]->FindPinChecked(EndParamName));
		}
		else
		{
			StartTimeKnots[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[Idx - 1]->FindPinChecked(EndParamName));
		}
		StartTimeKnots[Idx]->GetOutputPin()->MakeLinkTo(AddTimeEventFunctions[Idx]->FindPinChecked(StartParamName));
	}

	UEdGraphPin* PreUnbindThenPin = nullptr;
	UK2Node_IfThenElse* UnbindEventIfThenElse = CompilerContext.SpawnIntermediateNode<UK2Node_IfThenElse>(this, SourceGraph);
	UnbindEventIfThenElse->AllocateDefaultPins(); 
	UnbindEventIfThenElse->GetConditionPin()->MakeLinkTo(DoOnceVar->GetVariablePin());
	CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(UnbindPinName), *UnbindEventIfThenElse->GetExecPin());
	PreUnbindThenPin = UnbindEventIfThenElse->GetThenPin();

	UK2Node_AssignmentStatement* UnbindEventAssignment = CompilerContext.SpawnIntermediateNode<UK2Node_AssignmentStatement>(this, SourceGraph);
	UnbindEventAssignment->AllocateDefaultPins();
	UnbindEventAssignment->GetVariablePin()->MakeLinkTo(DoOnceVar->GetVariablePin());
	UnbindEventAssignment->PostReconstructNode();
	UnbindEventAssignment->GetValuePin()->DefaultValue = TEXT("false");
	PreUnbindThenPin->MakeLinkTo(UnbindEventAssignment->GetExecPin());
	PreUnbindThenPin = UnbindEventAssignment->GetThenPin();

	for (int32 Idx = 0; Idx < EventsNumber; ++Idx)
	{
		UK2Node_CallFunction* RemoveTimeEventFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
		RemoveTimeEventFunction->SetFromFunction(RemoveGameTimeDurationEventsFunction);
		RemoveTimeEventFunction->AllocateDefaultPins();
		StartTimeKnots[Idx]->GetOutputPin()->MakeLinkTo(RemoveTimeEventFunction->FindPinChecked(TEXT("Date")));
		TimeEvents[Idx]->FindPinChecked(UK2Node_CustomEvent::DelegateOutputName)->MakeLinkTo(RemoveTimeEventFunction->FindPinChecked(EventParamName));

		PreUnbindThenPin->MakeLinkTo(RemoveTimeEventFunction->GetExecPin());
		PreUnbindThenPin = RemoveTimeEventFunction->GetThenPin();
	}
}

bool UBPNode_AddGameTimeDurationEvents::IsCompatibleWithGraph(const UEdGraph* TargetGraph) const
{
	EGraphType GraphType = TargetGraph->GetSchema()->GetGraphType(TargetGraph);
	return Super::IsCompatibleWithGraph(TargetGraph) && GraphType == EGraphType::GT_Ubergraph || GraphType == EGraphType::GT_Macro;
}

void UBPNode_AddGameTimeDurationEvents::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		FToolMenuSection& Section = Menu->AddSection(TEXT("GameTimeSystem"), LOCTEXT("时间系统", "时间系统"));

		if (Context->Pin != nullptr)
		{
			// we only do this for normal BlendList/BlendList by enum, BlendList by Bool doesn't support add/remove pins
			if (Context->Pin->Direction == EGPD_Output && EventsNumber > 2 && Context->Pin->GetDisplayName().ToString().Contains(EventName))
			{
				Section.AddMenuEntry(
					TEXT("RemoveTimeEvent"),
					LOCTEXT("移除该事件", "移除该事件"),
					LOCTEXT("移除该事件", "移除该事件"),
					FSlateIcon(),
					FUIAction(
						FExecuteAction::CreateUObject(const_cast<UBPNode_AddGameTimeDurationEvents*>(this), &UBPNode_AddGameTimeDurationEvents::RemoveEvent)
					)
				);
			}
		}
		Section.AddMenuEntry(
			TEXT("AddTimeEvent"),
			LOCTEXT("增加时间事件", "增加时间事件"),
			LOCTEXT("增加时间事件", "增加时间事件"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateUObject(const_cast<UBPNode_AddGameTimeDurationEvents*>(this), &UBPNode_AddGameTimeDurationEvents::AddEvent)
			)
		);
	}
}

FText UBPNode_AddGameTimeDurationEvents::GetMenuCategory() const
{
	return LOCTEXT("游戏|时间系统", "游戏|时间系统");
}

FText UBPNode_AddGameTimeDurationEvents::MakeTimeNodeTitle(ENodeTitleType::Type TitleType, const FText& Title) const
{
	if (TitleType != ENodeTitleType::FullTitle)
	{
		return Title;
	}
	return FText::Format(LOCTEXT("TimeNodeFullTitle", "{0} [{1}]\n{2}"), Title, EventsNumber, GetClass()->GetDisplayNameText());
}

void UBPNode_AddGameTimeDurationEvents::AddEvent()
{
	EventsNumber += 1;
	ReconstructNode();
}

void UBPNode_AddGameTimeDurationEvents::RemoveEvent()
{
	EventsNumber -= 1;
	ReconstructNode();
}

UBPNode_AddEveryHourCircleEvents::UBPNode_AddEveryHourCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryHourEvent_Duration));
	RemoveGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, RemoveEveryHourEvent));
	GameTimeConfigType = FXD_EveryHourConfig::StaticStruct();
}

FText UBPNode_AddEveryHourCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return MakeTimeNodeTitle(TitleType, LOCTEXT("Add Every Hour Circle Events", "Add Every Hour Circle Events"));
}

UBPNode_AddEveryDayCircleEvents::UBPNode_AddEveryDayCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryDayEvent_Duration));
	RemoveGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, RemoveEveryDayEvent));
	GameTimeConfigType = FXD_EveryDayConfig::StaticStruct();
}

FText UBPNode_AddEveryDayCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return MakeTimeNodeTitle(TitleType, LOCTEXT("Add Every Day Circle Events", "Add Every Day Circle Events"));
}

UBPNode_AddEveryWeekCircleEvents::UBPNode_AddEveryWeekCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryWeekEvent_Duration));
	RemoveGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, RemoveEveryWeekEvent));
	GameTimeConfigType = FXD_EveryWeekConfig::StaticStruct();
}

FText UBPNode_AddEveryWeekCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return MakeTimeNodeTitle(TitleType, LOCTEXT("Add Every Week Circle Events", "Add Every Week Circle Events"));
}

UBPNode_AddEveryMonthCircleEvents::UBPNode_AddEveryMonthCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryMonthEvent_Duration));
	RemoveGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, RemoveEveryMonthEvent));
	GameTimeConfigType = FXD_EveryMonthConfig::StaticStruct();
}

FText UBPNode_AddEveryMonthCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return MakeTimeNodeTitle(TitleType, LOCTEXT("Add Every Month Circle Events", "Add Every Month Circle Events"));
}

UBPNode_AddEveryYearCircleEvents::UBPNode_AddEveryYearCircleEvents()
{
	AddGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, AddEveryYearEvent_Duration));
	RemoveGameTimeDurationEventsFunction = UXD_TimeManagerFunctionLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UXD_TimeManagerFunctionLibrary, RemoveEveryYearEvent));
	GameTimeConfigType = FXD_EveryYearConfig::StaticStruct();
}

FText UBPNode_AddEveryYearCircleEvents::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return MakeTimeNodeTitle(TitleType, LOCTEXT("Add Every Year Circle Events", "Add Every Year Circle Events"));
}

#undef LOCTEXT_NAMESPACE
