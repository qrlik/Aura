// Copyright by Aura

#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

AuraGameplayTags AuraGameplayTags::GameplayTags;

AuraGameplayTags& AuraGameplayTags::Get() {
	return GameplayTags;
}

void AuraGameplayTags::InitializeNativeTags() {
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName{ "Attributes.Secondary.Armor" }, FString{ "Reduces damage taken, improves Block Chance" });
}

//AuraGameplayTags::AuraGameplayTags() {
// InitializeNativeTags();
//}
