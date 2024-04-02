// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaMagnitudeCalculation.generated.h"

UCLASS()
class AURA_API UMaxManaMagnitudeCalculation : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()

public:
	UMaxManaMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDefinition;
};
