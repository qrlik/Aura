// Copyright by Aura

#include "UI/WidgetDataController/AttributeWidgetDataController.h"

#include "AbilitySystem/Data/AttributeInfo.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeWidgetDataController::BroadcastInitialValues() {
	for (const auto& AttributeInfo : AttributeInformation->GetAttributesInformation()) {
		const auto Value = AttributeInfo.Attribute.GetNumericValueChecked(AttributeSet);
		AttributeInfoDelegate.Broadcast(AttributeInfo, Value);
	}
}

void UAttributeWidgetDataController::BindCallbacksToDependencies() {
	for (const auto& AttributeInfo : AttributeInformation->GetAttributesInformation()) {
		auto& ChangeDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeInfo.Attribute);
		ensure(!ChangeDelegate.IsBoundToObject(this));
		ChangeDelegate.AddUObject(this, &UAttributeWidgetDataController::OnAttributeChange);
	}
}

void UAttributeWidgetDataController::OnAttributeChange(const FOnAttributeChangeData& ChangedAttribute) const {
	const auto& AttributeInfo = AttributeInformation->FindAttributeInfoByAttribute(ChangedAttribute.Attribute);
	AttributeInfoDelegate.Broadcast(AttributeInfo, ChangedAttribute.NewValue);
}
