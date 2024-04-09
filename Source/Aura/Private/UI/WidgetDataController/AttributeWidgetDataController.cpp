// Copyright by Aura

#include "UI/WidgetDataController/AttributeWidgetDataController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeWidgetDataController::BroadcastInitialValues() {
	auto Info = AttributeInformation->FindAttributeInfoByTag(AuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeWidgetDataController::BindCallbacksToDependencies() {
}
