// Copyright by Aura


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAbilitySystemTypes.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

namespace {
	struct AuraDamageStatics {
		// DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

		FGameplayEffectAttributeCaptureDefinition ArmorPenetrationDef;
		FGameplayEffectAttributeCaptureDefinition CriticalHitChanceDef;
		FGameplayEffectAttributeCaptureDefinition CriticalHitDamageDef;

		AuraDamageStatics():
			ArmorPenetrationDef(UAuraAttributeSet::GetArmorPenetrationAttribute(), EGameplayEffectAttributeCaptureSource::Source, true),
			CriticalHitChanceDef(UAuraAttributeSet::GetCriticalHitChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, true),
			CriticalHitDamageDef(UAuraAttributeSet::GetCriticalHitDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true) {
			// need to make UAuraAttributeSet::Armor public
			// also no need to capture not snapshot attribute, because we can get them directly from ASC
			// DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, EGameplayEffectAttributeCaptureSource::Target, false);
		}
	};

	const AuraDamageStatics& DamageStatics() {
		static AuraDamageStatics DStatics;
		return DStatics;
	}

	float GetCapturedAttribute(const FGameplayEffectAttributeCaptureDefinition& AttributeDef, const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                           const FAggregatorEvaluateParameters& EvalParams) {
		float CapturedAttribute = 0.f;
		ensure(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttributeDef, EvalParams, CapturedAttribute));
		return CapturedAttribute;
	}
}

UExecCalc_Damage::UExecCalc_Damage() {
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	auto* SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto* TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();
	const auto Source = TScriptInterface<ICombatInterface>(SourceAsc->GetAvatarActor());
	const auto Target = TScriptInterface<ICombatInterface>(TargetAsc->GetAvatarActor());
	const auto SourceLevel = (Source) ? Source->GetPlayerLevel() : 1;
	const auto TargetLevel = (Target) ? Target->GetPlayerLevel() : 1;

	const auto& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	auto Damage = Spec.GetSetByCallerMagnitude(AuraGameplayTags::Get().Damage);
	const auto IsBlocked = ProcessBlock(Damage, TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetBlockChanceAttribute()));

	// TO DO Check when context will be destroyed
	auto* Context = UAuraAbilitySystemLibrary::GetEffectContext(Spec.GetContext());
	Context->SetIsBlockedHit(IsBlocked);

	const auto Armor = TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetArmorAttribute());
	const auto EffectiveArmor = GetEffectiveArmor(Armor, SourceLevel, EvaluateParameters, ExecutionParams);
	ProcessArmor(Damage, EffectiveArmor, TargetLevel);

	auto CriticalResistance = TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetCriticalHitResistanceAttribute());
	CriticalResistance *= CriticalChanceResistanceCoefficient.GetValueAtLevel(TargetLevel);
	const auto IsCritical = ProcessCritical(Damage, CriticalResistance, EvaluateParameters, ExecutionParams);
	Context->SetIsCriticalHit(IsCritical);

	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

float UExecCalc_Damage::GetEffectiveArmor(float Armor, float Level, const FAggregatorEvaluateParameters& EvalParams,
                                          const FGameplayEffectCustomExecutionParameters& ExecutionParams) const {
	const float ArmorPenetration = GetCapturedAttribute(DamageStatics().ArmorPenetrationDef, ExecutionParams, EvalParams);
	Armor -= Armor * ArmorPenetration * ArmorPenetrationCoefficient.GetValueAtLevel(Level) / 100.f;
	return FMath::Clamp(Armor, 0.f, Armor);
}

bool UExecCalc_Damage::ProcessBlock(float& Damage, float BlockChance) const {
	const auto BlockRoll = FMath::RandRange(0.f, 100.f);
	if (BlockRoll < BlockChance) {
		Damage *= BlockFactor;
		return true;
	}
	return false;
}

void UExecCalc_Damage::ProcessArmor(float& Damage, float Armor, float Level) const {
	Damage -= Damage * Armor * EffectiveArmorCoefficient.GetValueAtLevel(Level) / 100.f;
	Damage = FMath::Clamp(Damage, 0.f, Damage);
}

bool UExecCalc_Damage::ProcessCritical(float& Damage, float CriticalResistance, const FAggregatorEvaluateParameters& EvalParams,
                                       const FGameplayEffectCustomExecutionParameters& ExecutionParams) const {
	auto CriticalChance = GetCapturedAttribute(DamageStatics().CriticalHitChanceDef, ExecutionParams, EvalParams);
	CriticalChance -= CriticalResistance;
	const auto CriticalRoll = FMath::RandRange(0.f, 100.f);
	if (CriticalRoll < CriticalChance) {
		const auto CriticalDamage = GetCapturedAttribute(DamageStatics().CriticalHitChanceDef, ExecutionParams, EvalParams);
		Damage = (Damage * 2.f) + CriticalDamage;
		return true;
	}
	return false;
}
