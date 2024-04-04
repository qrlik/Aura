// Copyright by Aura

#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

AuraGameplayTags AuraGameplayTags::GameplayTags;

const AuraGameplayTags& AuraGameplayTags::Get() {
	return GameplayTags;
}

AuraGameplayTags::AuraGameplayTags() {
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName{ "Attributes.Secondary.Armor" }, FString{ "Reduces damage taken, improves Block Chance" });
}
