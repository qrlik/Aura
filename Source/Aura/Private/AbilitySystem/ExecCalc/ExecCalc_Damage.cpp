// Copyright by Aura


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

namespace {
	struct AuraDamageStatics {
		// DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

		FGameplayEffectAttributeCaptureDefinition ArmorDef;

		AuraDamageStatics():
			ArmorDef(UAuraAttributeSet::GetArmorAttribute(), EGameplayEffectAttributeCaptureSource::Target, false) {
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
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	auto* SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();
	auto* TargetAsc = ExecutionParams.GetTargetAbilitySystemComponent();

	auto* Source = SourceAsc->GetAvatarActor();
	auto* Target = TargetAsc->GetAvatarActor();

	const auto& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	auto Damage = Spec.GetSetByCallerMagnitude(AuraGameplayTags::Get().Damage);
	ProcessBlock(Damage, TargetAsc->GetNumericAttributeChecked(UAuraAttributeSet::GetBlockChanceAttribute()));

	//float Armor = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, Armor);
	//++Armor;

	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UExecCalc_Damage::ProcessBlock(float& Damage, float BlockChance) const {
	const auto Block = FMath::RandRange(0.f, 100.f);
	if (Block < BlockChance) {
		Damage *= BlockFactor;
	}
}

