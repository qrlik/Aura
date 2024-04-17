// Copyright by Aura

#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& GameplayTag, bool bLogNotFound) const {
	for (const auto& InputAction : AbilityInputActions) {
		if (InputAction.InputTag.MatchesTagExact(GameplayTag)) {
			ensure(InputAction.InputAction);
			return InputAction.InputAction;
		}
	}
	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("UAuraInputConfig can't find InputAction for GameplayTag %s in %s"), *GameplayTag.ToString(), *GetName());
	}
	return nullptr;
}

const TArray<FAuraInputAction>& UAuraInputConfig::GetAbilityInputActions() const {
	return AbilityInputActions;
}
