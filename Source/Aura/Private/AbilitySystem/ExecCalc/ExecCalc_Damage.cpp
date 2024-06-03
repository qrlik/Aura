// Copyright by Aura


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

namespace {
	struct AuraDamageStatics {
		// DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

		FGameplayEffectAttributeCaptureDefinition ArmorPenetrationDef;

		AuraDamageStatics():
			ArmorPenetrationDef(UAuraAttributeSet::GetArmorPenetrationAttribute(), EGameplayEffectAttributeCaptureSource::Source, true) {
			// need to make UAuraAttributeSet::Armor public
			// also no need to capture not snapshot attribute, because we can get them directly from ASC
			// DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, EGameplayEffectAttributeCaptureSource::Target, false);
		}
	};

	const AuraDamageStatics& DamageStatics() {
		static AuraDamageStatics DStatics;
		return DStatics;
	}
}

UExecCalc_Damage::UExecCalc_Damage() {
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	auto* SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto* TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	auto Source = TScriptInterface<ICombatInterface>(SourceAsc->GetAvatarActor());
	auto Target = TScriptInterface<ICombatInterface>(TargetAsc->GetAvatarActor());
	const auto SourceLevel = (Source) ? Source->GetPlayerLevel() : 1;
	const auto TargetLevel = (Target) ? Target->GetPlayerLevel() : 1;

	const auto& Spec = ExecutionParams.GetOwningSpec();

	auto Damage = Spec.GetSetByCallerMagnitude(AuraGameplayTags::Get().Damage);
	ProcessBlock(Damage, TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetBlockChanceAttribute()));
	const auto Armor = TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetArmorAttribute());
	const auto EffectiveArmor = GetEffectiveArmor(Armor, SourceLevel, Spec, ExecutionParams);
	ProcessArmor(Damage, EffectiveArmor, TargetLevel);

	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

float UExecCalc_Damage::GetEffectiveArmor(float Armor, float Level, const FGameplayEffectSpec& Spec,
                                          const FGameplayEffectCustomExecutionParameters& ExecutionParams) const {
	float ArmorPenetration = 0.f;

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, ArmorPenetration);

	Armor -= Armor * ArmorPenetration * ArmorPenetrationCoefficient.GetValueAtLevel(Level) / 100.f;
	return FMath::Clamp(Armor, 0.f, Armor);
}

void UExecCalc_Damage::ProcessBlock(float& Damage, float BlockChance) const {
	const auto Block = FMath::RandRange(0.f, 100.f);
	if (Block < BlockChance) {
		Damage *= BlockFactor;
	}
}

void UExecCalc_Damage::ProcessArmor(float& Damage, float Armor, float Level) const {
	Damage -= Damage * Armor * EffectiveArmorCoefficient.GetValueAtLevel(Level) / 100.f;
	Damage = FMath::Clamp(Damage, 0.f, Damage);
}
