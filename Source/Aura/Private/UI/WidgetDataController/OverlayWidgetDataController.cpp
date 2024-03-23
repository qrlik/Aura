// Copyright by Aura

#include "UI/WidgetDataController/OverlayWidgetDataController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetDataController::BroadcastInitialValues() {
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}

void UOverlayWidgetDataController::BindCallbacksToDependencies() {
	BindAttributeValueChange(AttributeSet->GetHealthAttribute(), &UOverlayWidgetDataController::HealthChanged);
	BindAttributeValueChange(AttributeSet->GetMaxHealthAttribute(), &UOverlayWidgetDataController::MaxHealthChanged);
}

void UOverlayWidgetDataController::HealthChanged(const FOnAttributeChangeData& Data) const {
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetDataController::MaxHealthChanged(const FOnAttributeChangeData& Data) const {
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
