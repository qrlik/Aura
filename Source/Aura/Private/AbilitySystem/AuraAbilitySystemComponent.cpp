// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::InitializeComponent() {
	Super::InitializeComponent();

	BindDelegates();
}

void UAuraAbilitySystemComponent::OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
                                                        FActiveGameplayEffectHandle ActiveEffect) const {
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const auto& Tag : TagContainer) {
		// TODO Broadcast to Widget Data Controller
		FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}

void UAuraAbilitySystemComponent::BindDelegates() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::OnEffectAppliedToSelf);
}
