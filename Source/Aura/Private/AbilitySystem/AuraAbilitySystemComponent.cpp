// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::InitializeComponent() {
	Super::InitializeComponent();

	BindDelegates();
}

void UAuraAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) {
	for (const auto AbilityClass : Abilities) {
		FGameplayAbilitySpec Spec(AbilityClass, 1);
		// GiveAbility(Spec);
		GiveAbilityAndActivateOnce(Spec);
	}
}

void UAuraAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
                                                      FActiveGameplayEffectHandle ActiveEffect) const {
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnEffectAppliedToSelf.Broadcast(TagContainer);
}

void UAuraAbilitySystemComponent::BindDelegates() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectAppliedToSelf);
}
