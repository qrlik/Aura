// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemTypes.h"

UScriptStruct* FAuraAbilitySystemTypes::GetScriptStruct() const {
	return FAuraAbilitySystemTypes::StaticStruct();
}

bool FAuraAbilitySystemTypes::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) {
	return FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
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
