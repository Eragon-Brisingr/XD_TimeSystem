// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XD_PropertyCustomizationEx.h"

/**
 * 
 */
class XD_TIMESYSTEM_EDITOR_API FXD_GameTime_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_GameTime_Customization>
{
public:
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
};

class XD_TIMESYSTEM_EDITOR_API FXD_EveryHourConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_EveryHourConfig_Customization>
{
public:
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
};

class XD_TIMESYSTEM_EDITOR_API FXD_EveryDayConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_EveryDayConfig_Customization>
{
public:
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
};

 class XD_TIMESYSTEM_EDITOR_API FXD_EveryWeekConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_EveryWeekConfig_Customization>
 {
 public:
	 FXD_EveryWeekConfig_Customization();

 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}

	TArray<TSharedPtr<FString>> WeekEnumNameList;
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_EveryMonthConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_EveryMonthConfig_Customization>
 {
 public:
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_EveryYearConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_EveryYearConfig_Customization>
 {
 public:
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_SpecialTimeConfig_Customization : public IPropertyTypeCustomizationMakeInstanceable<FXD_SpecialTimeConfig_Customization>
 {
 public:
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 };
