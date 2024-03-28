// Copyright by Aura

#include "UI/WidgetDataController/OverlayWidgetDataController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetDataController::BroadcastInitialValues() {
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AttributeSet->GetMaxMana());
}

void UOverlayWidgetDataController::BindCallbacksToDependencies() {
	BindAttributeValueChange(AttributeSet->GetHealthAttribute(), &UOverlayWidgetDataController::HealthChanged);
	BindAttributeValueChange(AttributeSet->GetMaxHealthAttribute(), &UOverlayWidgetDataController::MaxHealthChanged);
	BindAttributeValueChange(AttributeSet->GetManaAttribute(), &UOverlayWidgetDataController::ManaChanged);
	BindAttributeValueChange(AttributeSet->GetMaxManaAttribute(), &UOverlayWidgetDataController::MaxManaChanged);

	AbilitySystemComponent->OnEffectAppliedToSelf.AddUObject(this, &UOverlayWidgetDataController::EffectAppliedToSelf);
}

void UOverlayWidgetDataController::InitializeImpl() {
	check(MessageWidgetByTag);
}

void UOverlayWidgetDataController::HealthChanged(const FOnAttributeChangeData& Data) const {
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetDataController::MaxHealthChanged(const FOnAttributeChangeData& Data) const {
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetDataController::ManaChanged(const FOnAttributeChangeData& Data) const {
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetDataController::MaxManaChanged(const FOnAttributeChangeData& Data) const {
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetDataController::EffectAppliedToSelf(const FGameplayTagContainer& EffectTags) const {
	for (const auto& EffectTag : EffectTags) {
		auto* Row = MessageWidgetByTag->FindRow<FMessageWidgetByTagRow>(EffectTag.GetTagName(), TEXT(""), false);
	}
}
