// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemTypes.h"

FGameplayEffectContext* FAuraGameplayEffectContext::Duplicate() const {
	auto* NewContext = new FAuraGameplayEffectContext();
	*NewContext = *this;
	if (GetHitResult()) {
		NewContext->AddHitResult(*GetHitResult(), true);
	}
	return NewContext;
}

UScriptStruct* FAuraGameplayEffectContext::GetScriptStruct() const {
	return StaticStruct();
}

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) {
	const auto Result = Super::NetSerialize(Ar, Map, bOutSuccess);

	uint8 RepBits = 0;
	if (Ar.IsSaving()) {
		RepBits |= (bIsBlockedHit << 0);
		RepBits |= (bIsCriticalHit << 1);
	}
	Ar.SerializeBits(&RepBits, 2);

	if (Ar.IsLoading()) {
		bIsBlockedHit = RepBits & (1 << 0);
		bIsCriticalHit = RepBits & (1 << 1);
	}

	return Result;
}

bool FAuraGameplayEffectContext::IsCriticalHit() const {
	return bIsCriticalHit;
}

bool FAuraGameplayEffectContext::IsBlockedHit() const {
	return bIsBlockedHit;
}

void FAuraGameplayEffectContext::SetIsCriticalHit(bool State) {
	bIsCriticalHit = State;
}

void FAuraGameplayEffectContext::SetIsBlockedHit(bool State) {
	bIsBlockedHit = State;
}
