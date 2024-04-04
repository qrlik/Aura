// Copyright by Aura

#pragma once

#include "CoreMinimal.h"

class AURA_API AuraGameplayTags {
public:
	static const AuraGameplayTags& Get();

private:
	AuraGameplayTags();

	static AuraGameplayTags GameplayTags;
};
