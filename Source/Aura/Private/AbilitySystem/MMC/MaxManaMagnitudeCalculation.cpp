// Copyright by Aura

#include "AbilitySystem/MMC/MaxManaMagnitudeCalculation.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMaxManaMagnitudeCalculation::UMaxManaMagnitudeCalculation() {
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

float UMaxManaMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluateParameters, Intelligence);
	ensure(Intelligence > 0.f || FMath::IsNearlyEqual(Intelligence, 0.f));

	const TScriptInterface<ICombatInterface> CombatInterface = Spec.GetContext().GetSourceObject();
	check(CombatInterface);
	const auto PlayerLevel = (CombatInterface) ? CombatInterface->GetPlayerLevel() : 0;

	return 2.5f * Intelligence + 15.f * PlayerLevel;
}
