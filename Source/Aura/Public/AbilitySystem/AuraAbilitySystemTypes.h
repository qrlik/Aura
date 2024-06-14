// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "AuraAbilitySystemTypes.generated.h"

USTRUCT()
struct AURA_API FAuraGameplayEffectContext : public FGameplayEffectContext {
	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* Duplicate() const override;
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

template <>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FGameplayEffectContext> {
	enum {
		WithNetSerializer = true,
		WithCopy = true
	};
};
