// Copyright by Aura

#include "AbilitySystem/MMC/MaxHealthMagnitudeCalculation.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMaxHealthMagnitudeCalculation::UMaxHealthMagnitudeCalculation() {
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMaxHealthMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluateParameters, Vigor);
	//Vigor = FMath::Max<float>(Vigor, 0.f);
	ensure(Vigor > 0.f || FMath::IsNearlyEqual(Vigor, 0.f));

	const TScriptInterface<ICombatInterface> CombatInterface = Spec.GetContext().GetSourceObject();
	check(CombatInterface);
	const auto PlayerLevel = (CombatInterface) ? CombatInterface->GetPlayerLevel() : 0;

	return 2.5f * Vigor + 10.f * PlayerLevel;
}
