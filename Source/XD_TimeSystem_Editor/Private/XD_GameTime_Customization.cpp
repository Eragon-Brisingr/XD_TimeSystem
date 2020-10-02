// Fill out your copyright notice in the Description page of Project Settings.

#include "XD_GameTime_Customization.h"
#include <DetailWidgetRow.h>
#include <Widgets/SBoxPanel.h>
#include <Widgets/Input/SNumericEntryBox.h>
#include <IDetailChildrenBuilder.h>
#include <Widgets/Input/STextComboBox.h>

#include "XD_TimeSystemType.h"

#define LOCTEXT_NAMESPACE "XD_TimeSystem_Editor"

constexpr float HorizontolPadding = 5.f;
constexpr float VerticalPadding = 0.f;

namespace GameTimePropertyCustomize
{
	UObject* GetOuter(const TSharedRef<IPropertyHandle>& PropertyHandle)
	{
		TArray<UObject*> Outers;
		PropertyHandle->GetOuterObjects(Outers);
		return Outers.Num() > 0 ? Outers[0] : nullptr;
	}

	template<typename ValueType>
	ValueType GetValue(const TSharedPtr<IPropertyHandle>& PropertyHandle)
	{
		if (UObject* Outer = GetOuter(PropertyHandle.ToSharedRef()))
		{
			if (ValueType* Res = reinterpret_cast<ValueType*>(PropertyHandle->GetValueBaseAddress(reinterpret_cast<uint8*>(Outer))))
			{
				return *Res;
			}
		}
		return {};
	}

	template<typename Type>
	void SetValue(const TSharedPtr<IPropertyHandle>& PropertyHandle, const Type& Value, bool NotifyChange = true)
	{
		if (NotifyChange)
		{
			PropertyHandle->NotifyPreChange();
		}
		if (Type* Target = reinterpret_cast<Type*>(PropertyHandle->GetValueBaseAddress(reinterpret_cast<uint8*>(GetOuter(PropertyHandle.ToSharedRef())))))
		{
			*Target = Value;
			if (NotifyChange)
			{
				PropertyHandle->NotifyPostChange(EPropertyValueSetFlags::DefaultFlags);
			}
		}
	}
}

TSharedRef<SWidget> CreateGameTimeHeaderView(TSharedRef<class IPropertyHandle> StructPropertyHandle)
{
	return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
					.Text(LOCTEXT("年", "年"))
			]
			+ SHorizontalBox::Slot()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
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
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetYear());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetYear(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
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
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetMonth());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetMonth(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				.AutoWidth()
			[
				SNew(SNumericEntryBox<int32>)
					.AllowSpin(true)
					.ToolTipText(LOCTEXT("日", "日"))
					.MinValue(FXD_GameTime::MinValue().GetDay())
					.MinSliderValue(FXD_GameTime::MinValue().GetDay())
					.MaxValue_Lambda([=]()
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(FXD_GameTime::DaysInMonth(GameTime.GetYear(), GameTime.GetMonth()));
					})
					.MaxSliderValue_Lambda([=]()
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(FXD_GameTime::DaysInMonth(GameTime.GetYear(), GameTime.GetMonth()));
					})
					.Delta(1)
					.MinDesiredValueWidth(25.0f)
					.IsEnabled(!StructPropertyHandle->IsEditConst())
					.Value_Lambda([=]()
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetDay());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetDay(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
					})
			];
}

TSharedRef<SWidget> CreateGameTimeBodyView(TSharedRef<class IPropertyHandle> StructPropertyHandle)
{
	return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
					.Text(LOCTEXT("时", "时"))
			]
			+ SHorizontalBox::Slot()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
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
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetHour());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetHour(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
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
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetMinute());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetMinute(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
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
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						return TOptional<int32>(GameTime.GetSecond());
					})
					.OnValueChanged_Lambda([=](int Value)
					{
						FXD_GameTime GameTime = GameTimePropertyCustomize::GetValue<FXD_GameTime>(StructPropertyHandle);
						GameTime.SetSecond(Value);
						GameTimePropertyCustomize::SetValue(StructPropertyHandle, GameTime);
					})
			];
}

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
			CreateGameTimeHeaderView(StructPropertyHandle)
		];
}

void FXD_GameTime_Customization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructBuilder.AddCustomRow(FText::GetEmpty())
		.ValueContent()
			.HAlign(HAlign_Fill)
		[
			CreateGameTimeBodyView(StructPropertyHandle)
		];
}

void FXD_EveryHourConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
						.Text(LOCTEXT("分", "分"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("分", "分"))
						.MinValue(FXD_GameTime::MinValue().GetMinute())
						.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
						.MaxValue(FXD_GameTime::MaxValue().GetMinute())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
 						.Value_Lambda([=]()
 						{
 							FXD_EveryHourConfig EveryHourConfig = GameTimePropertyCustomize::GetValue<FXD_EveryHourConfig>(StructPropertyHandle);
 							int32 Minute;
 							EveryHourConfig.GetConfig(Minute);
 							return TOptional<int32>(Minute);
 						})
 						.OnValueChanged_Lambda([=](int Value)
 						{
 							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryHourConfig(Value));
 						})
				]
		];
}

void FXD_EveryDayConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
						.Text(LOCTEXT("时", "时"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("时", "时"))
						.MinValue(FXD_GameTime::MinValue().GetHour())
						.MinSliderValue(FXD_GameTime::MinValue().GetHour())
						.MaxValue(FXD_GameTime::MaxValue().GetHour())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetHour())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryDayConfig EveryDayConfig = GameTimePropertyCustomize::GetValue<FXD_EveryDayConfig>(StructPropertyHandle);
							int32 Hour, Minute;
							EveryDayConfig.GetConfig(Hour, Minute);
							return TOptional<int32>(Hour);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryDayConfig EveryDayConfig = GameTimePropertyCustomize::GetValue<FXD_EveryDayConfig>(StructPropertyHandle);
							int32 Hour, Minute;
							EveryDayConfig.GetConfig(Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryDayConfig(Value, Minute));
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("分", "分"))
						.MinValue(FXD_GameTime::MinValue().GetMinute())
						.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
						.MaxValue(FXD_GameTime::MaxValue().GetMinute())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryDayConfig EveryDayConfig = GameTimePropertyCustomize::GetValue<FXD_EveryDayConfig>(StructPropertyHandle);
							int32 Hour, Minute;
							EveryDayConfig.GetConfig(Hour, Minute);
							return TOptional<int32>(Minute);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryDayConfig EveryDayConfig = GameTimePropertyCustomize::GetValue<FXD_EveryDayConfig>(StructPropertyHandle);
							int32 Hour, Minute;
							EveryDayConfig.GetConfig(Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryDayConfig(Hour, Value));
						})
				]
		];
}

FXD_EveryWeekConfig_Customization::FXD_EveryWeekConfig_Customization()
{
	if (const UEnum* DayOfWeek = StaticEnum<EXD_DayOfWeek>())
	{
		for (int32 Idx = 0; Idx < DayOfWeek->NumEnums() - 1; ++Idx)
		{
			WeekEnumNameList.Add(MakeShareable(new FString(DayOfWeek->GetDisplayNameTextByIndex(Idx).ToString())));
		}
	}
}

void FXD_EveryWeekConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
	int32 WeekDay, Hour, Minute;
	EveryWeekConfig.GetConfig(WeekDay, Hour, Minute);
	TSharedPtr<FString> SelectedItem = WeekDay < WeekEnumNameList.Num() ? WeekEnumNameList[WeekDay] : nullptr;

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
						.Text(LOCTEXT("周", "周"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(STextComboBox)
						.OptionsSource(&WeekEnumNameList)
						.OnSelectionChanged_Lambda([=](TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo)
						{
							if (SelectInfo == ESelectInfo::OnMouseClick)
							{
								int32 Value = WeekEnumNameList.IndexOfByKey(Selection);
								FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
								int32 WeekDay, Hour, Minute;
								EveryWeekConfig.GetConfig(WeekDay, Hour, Minute);
								GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryWeekConfig(Value, Hour, Minute));
							}
						})
						.InitiallySelectedItem(SelectedItem)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("时", "时"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("时", "时"))
						.MinValue(FXD_GameTime::MinValue().GetHour())
						.MinSliderValue(FXD_GameTime::MinValue().GetHour())
						.MaxValue(FXD_GameTime::MaxValue().GetHour())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetHour())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryWeekConfig.GetConfig(Day, Hour, Minute);
							return TOptional<int32>(Hour);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryWeekConfig.GetConfig(Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryWeekConfig(Day, Value, Minute));
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("分", "分"))
						.MinValue(FXD_GameTime::MinValue().GetMinute())
						.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
						.MaxValue(FXD_GameTime::MaxValue().GetMinute())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryWeekConfig.GetConfig(Day, Hour, Minute);
							return TOptional<int32>(Minute);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryWeekConfig EveryWeekConfig = GameTimePropertyCustomize::GetValue<FXD_EveryWeekConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryWeekConfig.GetConfig(Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryWeekConfig(Day, Hour, Value));
						})
				]
		];
}

void FXD_EveryMonthConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
						.Text(LOCTEXT("日", "日"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("日", "日"))
						.MinValue(1)
						.MinSliderValue(1)
						.MaxValue(31)
						.MaxSliderValue(31)
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							return TOptional<int32>(Day);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryMonthConfig(Value, Hour, Minute));
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("时", "时"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("时", "时"))
						.MinValue(FXD_GameTime::MinValue().GetHour())
						.MinSliderValue(FXD_GameTime::MinValue().GetHour())
						.MaxValue(FXD_GameTime::MaxValue().GetHour())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetHour())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							return TOptional<int32>(Hour);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryMonthConfig(Day, Value, Minute));
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("分", "分"))
						.MinValue(FXD_GameTime::MinValue().GetMinute())
						.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
						.MaxValue(FXD_GameTime::MaxValue().GetMinute())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							return TOptional<int32>(Minute);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryMonthConfig EveryMonthConfig = GameTimePropertyCustomize::GetValue<FXD_EveryMonthConfig>(StructPropertyHandle);
							int32 Day, Hour, Minute;
							EveryMonthConfig.GetConfig(Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryMonthConfig(Day, Hour, Value));
						})
				]
		];
}

void FXD_EveryYearConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
						.Text(LOCTEXT("月", "月"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("月", "月"))
						.MinValue(1)
						.MinSliderValue(1)
						.MaxValue(12)
						.MaxSliderValue(12)
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							return TOptional<int32>(Month);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryYearConfig(Value, Day, Hour, Minute));
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
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("日", "日"))
						.MinValue(1)
						.MinSliderValue(1)
						.MaxValue(31)
						.MaxSliderValue(31)
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							return TOptional<int32>(Day);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryYearConfig(Month, Value, Hour, Minute));
						})
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("时", "时"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("时", "时"))
						.MinValue(FXD_GameTime::MinValue().GetHour())
						.MinSliderValue(FXD_GameTime::MinValue().GetHour())
						.MaxValue(FXD_GameTime::MaxValue().GetHour())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetHour())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							return TOptional<int32>(Hour);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryYearConfig(Month, Day, Value, Minute));
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
				.Padding(HorizontolPadding, VerticalPadding).VAlign(VAlign_Center)
				[
					SNew(SNumericEntryBox<int32>)
						.AllowSpin(true)
						.ToolTipText(LOCTEXT("分", "分"))
						.MinValue(FXD_GameTime::MinValue().GetMinute())
						.MinSliderValue(FXD_GameTime::MinValue().GetMinute())
						.MaxValue(FXD_GameTime::MaxValue().GetMinute())
						.MaxSliderValue(FXD_GameTime::MaxValue().GetMinute())
						.Delta(1)
						.MinDesiredValueWidth(30.0f)
						.IsEnabled(!StructPropertyHandle->IsEditConst())
						.Value_Lambda([=]()
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							return TOptional<int32>(Minute);
						})
						.OnValueChanged_Lambda([=](int Value)
						{
							FXD_EveryYearConfig EveryYearConfig = GameTimePropertyCustomize::GetValue<FXD_EveryYearConfig>(StructPropertyHandle);
							int32 Month, Day, Hour, Minute;
							EveryYearConfig.GetConfig(Month, Day, Hour, Minute);
							GameTimePropertyCustomize::SetValue(StructPropertyHandle, FXD_EveryYearConfig(Month, Day, Hour, Value));
						})
				]
		];
}

void FXD_SpecialTimeConfig_Customization::CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TSharedPtr<IPropertyHandle> SpecialTime_TimeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FXD_SpecialTimeConfig, SpecialTime));
	HeaderRow.FilterString(StructPropertyHandle->GetPropertyDisplayName())
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
			.HAlign(HAlign_Fill)
		[
			CreateGameTimeHeaderView(SpecialTime_TimeHandle.ToSharedRef())
		];
}

void FXD_SpecialTimeConfig_Customization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	TSharedPtr<IPropertyHandle> SpecialTime_TimeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FXD_SpecialTimeConfig, SpecialTime));
	StructBuilder.AddCustomRow(FText::GetEmpty())
		.ValueContent()
		.HAlign(HAlign_Fill)
		[
			CreateGameTimeBodyView(SpecialTime_TimeHandle.ToSharedRef())
		];
}

#undef LOCTEXT_NAMESPACE
