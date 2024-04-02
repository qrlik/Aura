// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthMagnitudeCalculation.generated.h"

UCLASS()
class AURA_API UMaxHealthMagnitudeCalculation : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()

public:
	UMaxHealthMagnitudeCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDefinition;
};
