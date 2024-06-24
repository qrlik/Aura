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
	float GetEffectiveArmor(float Armor, float Level, const FAggregatorEvaluateParameters& EvalParams,
	                        const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;

	bool ProcessBlock(float& Damage, float BlockChance) const;
	void ProcessArmor(float& Damage, float Armor, float Level) const;
	bool ProcessCritical(float& Damage, float CriticalResistance, const FAggregatorEvaluateParameters& EvalParams,
	                     const FGameplayEffectCustomExecutionParameters& ExecutionParams) const;

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat ArmorPenetrationCoefficient;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat EffectiveArmorCoefficient;
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat CriticalChanceResistanceCoefficient;

	UPROPERTY(EditDefaultsOnly)
	float BlockFactor = 0.5f;
};
