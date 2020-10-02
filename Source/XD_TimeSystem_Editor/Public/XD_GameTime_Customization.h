// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"

/**
 * 
 */
class XD_TIMESYSTEM_EDITOR_API FXD_GameTime_Customization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_GameTime_Customization()); }
	
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
};

class XD_TIMESYSTEM_EDITOR_API FXD_EveryHourConfig_Customization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_EveryHourConfig_Customization()); }
	
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
};

class XD_TIMESYSTEM_EDITOR_API FXD_EveryDayConfig_Customization : public IPropertyTypeCustomization
{
public:
    static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_EveryDayConfig_Customization()); }
	
	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
};

 class XD_TIMESYSTEM_EDITOR_API FXD_EveryWeekConfig_Customization : public IPropertyTypeCustomization
 {
 public:
     static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_EveryWeekConfig_Customization()); }
 	
	 FXD_EveryWeekConfig_Customization();

 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}

	TArray<TSharedPtr<FString>> WeekEnumNameList;
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_EveryMonthConfig_Customization : public IPropertyTypeCustomization
 {
 public:
     static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_EveryMonthConfig_Customization()); }
 	
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_EveryYearConfig_Customization : public IPropertyTypeCustomization
 {
 public:
     static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_EveryYearConfig_Customization()); }
 	
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override{}
 };
 
 class XD_TIMESYSTEM_EDITOR_API FXD_SpecialTimeConfig_Customization : public IPropertyTypeCustomization
 {
 public:
     static TSharedRef<IPropertyTypeCustomization> MakeInstance() { return MakeShareable(new FXD_SpecialTimeConfig_Customization()); }
 	
 	/** IPropertyTypeCustomization interface */
 	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
 };
