// Copyright by Aura

#include "UI/WidgetDataController/OverlayWidgetDataController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetDataController::BroadcastInitialValues() {
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}
