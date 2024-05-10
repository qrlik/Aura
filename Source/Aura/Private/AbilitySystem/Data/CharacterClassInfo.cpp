// Copyright by Aura

#include "AbilitySystem/Data/CharacterClassInfo.h"

const FCharacterClassDefaultInfo& UCharacterClassInfo::GetClassInfo(ECharacterClass Class) {
	return ClassesInfo.FindChecked(Class);
}
