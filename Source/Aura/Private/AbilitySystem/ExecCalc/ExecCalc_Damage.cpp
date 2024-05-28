// Copyright by Aura


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"

UExecCalc_Damage::UExecCalc_Damage() {
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	auto* SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto* TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	auto* Source = SourceAsc->GetAvatarActor();
	auto* Target = TargetAsc->GetAvatarActor();

	const auto& Spec = ExecutionParams.GetOwningSpec();
}
