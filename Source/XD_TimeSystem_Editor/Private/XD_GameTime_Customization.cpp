// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_GameTime_Customization.h"
#include <DetailWidgetRow.h>
#include "XD_PropertyCustomizationEx.h"
#include "XD_TimeSystemType.h"
#include <SBoxPanel.h>
#include <SNumericEntryBox.h>
#include <IDetailChildrenBuilder.h>

#define LOCTEXT_NAMESPACE "XD_TimeSystem_Editor"

void FXD_GameTime_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	HeaderRow.FilterString(StructPropertyHandle->GetPropertyDisplayName())
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
			.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
					.Text(LOCTEXT("年", "年"))
			]
			+ SHorizontalBox::Slot()
				.Padding(5.f, 0.f, 5.f, 0.f)
				.AutoWidth()
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("年", "年"))
					.MinValue(FXD_GameTime::MinValue().GetYear())
					.MinSliderValue(FXD_GameTime::MinValue().GetYear())
					.MaxValue(FXD_GameTime::MaxValue().GetYear())
					.MaxSliderValue(FXD_GameTime::MaxValue().GetYear())
					.Delta(1)
					.MinDesiredValueWidth(40.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetYear());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetYear(Value);
					})
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("月", "月"))
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5.f, 0.f, 5.f, 0.f)
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("月", "月"))
					.MinValue(FXD_GameTime::MinValue().GetMonth())
					.MinSliderValue(FXD_GameTime::MinValue().GetMonth())
					.MaxValue(FXD_GameTime::MaxValue().GetMonth())
					.MaxSliderValue(FXD_GameTime::MaxValue().GetMonth())
					.Delta(1)
					.MinDesiredValueWidth(25.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetMonth());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetMonth(Value);
					})
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("日", "日"))
				]
			+ SHorizontalBox::Slot()
				.Padding(5.f, 0.f, 5.f, 0.f)
				.AutoWidth()
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("日", "日"))
					.MinValue(FXD_GameTime::MinValue().GetDay())
					.MinSliderValue(FXD_GameTime::MinValue().GetDay())
					.MaxValue_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(FXD_GameTime::DaysInMonth(GameTime.GetYear(), GameTime.GetMonth()));
					})
					.MaxSliderValue_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(FXD_GameTime::DaysInMonth(GameTime.GetYear(), GameTime.GetMonth()));
					})
					.Delta(1)
					.MinDesiredValueWidth(25.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetDay());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetDay(Value);
					})
			]
		];
}

void FXD_GameTime_Customization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructBuilder.AddCustomRow(FText::GetEmpty())
		.ValueContent()
			.HAlign(HAlign_Fill)
				[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
					.Text(LOCTEXT("时", "时"))
			]
			+ SHorizontalBox::Slot()
				.Padding(5.f, 0.f, 5.f, 0.f)
				.AutoWidth()
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("时", "时"))
					.MinValue(FXD_GameTime::MinValue().GetHour())
					.MinSliderValue(FXD_GameTime::MinValue().GetHour())
					.MaxValue(FXD_GameTime::MaxValue().GetHour())
					.MaxSliderValue(FXD_GameTime::MaxValue().GetHour())
					.Delta(1)
					.MinDesiredValueWidth(40.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetHour());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetHour(Value);
					})
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("分", "分"))
				]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5.f, 0.f, 5.f, 0.f)
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("分", "分"))
					.MinValue(FXD_GameTime::MinValue().GetMinute())
					.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
					.MaxValue(FXD_GameTime::MaxValue().GetMinute())
					.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
					.Delta(1)
					.MinDesiredValueWidth(25.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetMinute());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetMinute(Value);
					})
			]
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("秒", "秒"))
				]
			+ SHorizontalBox::Slot()
				.Padding(5.f, 0.f, 5.f, 0.f)
				.AutoWidth()
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("秒", "秒"))
					.MinValue(FXD_GameTime::MinValue().GetSecond())
					.MinSliderValue(FXD_GameTime::MinValue().GetSecond())
					.MaxValue(FXD_GameTime::MaxValue().GetSecond())
					.MaxSliderValue(FXD_GameTime::MaxValue().GetSecond())
					.Delta(1)
					.MinDesiredValueWidth(25.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetSecond());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime& GameTime = FPropertyCustomizeHelper::Value<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetSecond(Value);
					})
			]
		];
}

#undef LOCTEXT_NAMESPACE
