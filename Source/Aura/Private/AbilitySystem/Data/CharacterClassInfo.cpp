// Copyright by Aura

#include "AbilitySystem/Data/CharacterClassInfo.h"

const FCharacterClassDefaultInfo& UCharacterClassInfo::GetClassInfo(ECharacterClass Class) {
	return ClassesInfo.FindChecked(Class);
}

TArray<TSubclassOf<UGameplayAbility>> UCharacterClassInfo::GetAbilitiesClasses() const {
	return Abilities;
}

TSubclassOf<UGameplayEffect> UCharacterClassInfo::GetSecondaryAttributesClass() const {
	return SecondaryAttributes;
}

TSubclassOf<UGameplayEffect> UCharacterClassInfo::GetVitalAttributesClass() const {
	return VitalAttributes;
}
