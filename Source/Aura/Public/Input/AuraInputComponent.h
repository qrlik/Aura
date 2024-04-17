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
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType RealedFunc,
	                        HeldFuncType HeldFunc);
};

template <typename UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType RealedFunc,
                                             HeldFuncType HeldFunc) {
	for (const auto& AbilityInputAction : InputConfig->GetAbilityInputActions()) {
		check(AbilityInputAction.InputAction && AbilityInputAction.InputTag.IsValid());
		if (PressedFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AbilityInputAction.InputTag);
		}
		if (RealedFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Completed, Object, HeldFunc, AbilityInputAction.InputTag);
		}
		if (HeldFunc) {
			BindAction(AbilityInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AbilityInputAction.InputTag);
		}
	}
}
