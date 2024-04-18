// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::InitializeComponent() {
	Super::InitializeComponent();

	BindDelegates();
}

void UAuraAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) {
	for (const auto AbilityClass : Abilities) {
		FGameplayAbilitySpec Spec(AbilityClass, 1);
		if (const auto* Ability = Cast<UAuraGameplayAbility>(Spec.Ability)) {
			check(Ability->StartupInputTag.IsValid());
			Spec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
		}
		GiveAbility(Spec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag) {
	for (auto& Ability : GetActivatableAbilities()) {
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag)) {
			AbilitySpecInputReleased(Ability);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag) {
	for (auto& Ability : GetActivatableAbilities()) {
		if (Ability.DynamicAbilityTags.HasTagExact(InputTag)) {
			if (!Ability.IsActive()) {
				TryActivateAbility(Ability.Handle);
			}
			AbilitySpecInputPressed(Ability);
		}
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
