// Copyright by Aura

#include "UI/WidgetDataController/EnemyWidgetDataController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UEnemyWidgetDataController::BroadcastInitialValues() {
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}

void UEnemyWidgetDataController::BindCallbacksToDependencies() {
	BindAttributeValueChange(AttributeSet->GetHealthAttribute(), &UEnemyWidgetDataController::HealthChanged);
	BindAttributeValueChange(AttributeSet->GetMaxHealthAttribute(), &UEnemyWidgetDataController::MaxHealthChanged);
}

void UEnemyWidgetDataController::HealthChanged(const FOnAttributeChangeData& Data) const {
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UEnemyWidgetDataController::MaxHealthChanged(const FOnAttributeChangeData& Data) const {
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
