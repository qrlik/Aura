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
	void ProcessBlock(float& Damage, float BlockChance) const;

	UPROPERTY(EditDefaultsOnly)
	float BlockFactor = 0.5f;
};
