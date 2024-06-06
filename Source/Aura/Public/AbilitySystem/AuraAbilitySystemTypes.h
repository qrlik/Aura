// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AuraAbilitySystemTypes.generated.h"

USTRUCT()
struct AURA_API FAuraAbilitySystemTypes : public FGameplayEffectContext {
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const override;
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	bool IsCriticalHit() const;
	bool IsBlockedHit() const;
	void SetIsCriticalHit(bool State);
	void SetIsBlockedHit(bool State);

private:
	UPROPERTY()
	uint8 bIsBlockedHit : 1 = false;

	UPROPERTY()
	uint8 bIsCriticalHit : 1 = false;
};
