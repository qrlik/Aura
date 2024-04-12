// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer&);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent {
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;

	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	FEffectAssetTagsSignature OnEffectAppliedToSelf;

protected:
	void EffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	                         FActiveGameplayEffectHandle ActiveEffect) const;

private:
	void BindDelegates();
};
