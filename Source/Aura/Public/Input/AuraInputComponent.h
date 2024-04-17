// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent {
	GENERATED_BODY()

public:
	template <typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindInputActionsToTags(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
	                            HeldFuncType HeldFunc);
};

template <typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindInputActionsToTags(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
                                                 ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc) {
	for (const auto& AbilityInputAction : InputConfig->GetAbilityInputActions()) {
		check(AbilityInputAction.InputAction && AbilityInputAction.InputTag.IsValid());
		if (PressedFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityInputAction.InputTag);
		}
		if (ReleasedFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AbilityInputAction.InputTag);
		}
		if (HeldFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityInputAction.InputTag);
		}
	}
}
