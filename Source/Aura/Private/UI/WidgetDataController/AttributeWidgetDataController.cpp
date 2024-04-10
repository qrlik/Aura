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
}
