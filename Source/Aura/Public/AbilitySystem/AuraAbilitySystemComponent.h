// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent {
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;

protected:
	void OnEffectAppliedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	                           FActiveGameplayEffectHandle ActiveEffect) const;

private:
	void BindDelegates();
};
