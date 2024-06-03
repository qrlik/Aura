// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

UCLASS(Abstract)
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation {
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	float GetEffectiveArmor(float Armor, const FGameplayEffectSpec& Spec, const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;
	void ProcessBlock(float& Damage, float BlockChance) const;
	void ProcessArmor(float& Damage, float Armor) const;

	UPROPERTY(EditDefaultsOnly)
	float BlockFactor = 0.5f;
};
