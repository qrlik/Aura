// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemTypes.h"

UScriptStruct* FAuraAbilitySystemTypes::GetScriptStruct() const {
	return FAuraAbilitySystemTypes::StaticStruct();
}

bool FAuraAbilitySystemTypes::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) {
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

bool FAuraAbilitySystemTypes::IsCriticalHit() const {
	return bIsCriticalHit;
}

bool FAuraAbilitySystemTypes::IsBlockedHit() const {
	return bIsBlockedHit;
}

void FAuraAbilitySystemTypes::SetIsCriticalHit(bool State) {
	bIsCriticalHit = State;
}

void FAuraAbilitySystemTypes::SetIsBlockedHit(bool State) {
	bIsBlockedHit = State;
}
