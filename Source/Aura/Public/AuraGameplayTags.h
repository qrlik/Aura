// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class AURA_API AuraGameplayTags {
public:
	static AuraGameplayTags& Get();
	static void InitializeNativeTags();

	FGameplayTag Attributes_Secondary_Armor;

private:
	//AuraGameplayTags();

	static AuraGameplayTags GameplayTags;
};
