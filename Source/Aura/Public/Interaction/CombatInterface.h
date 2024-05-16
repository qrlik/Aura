// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UCombatInterface : public UInterface {
	GENERATED_BODY()
};

class AURA_API ICombatInterface {
	GENERATED_BODY()

public:
	virtual FVector GetCombatSocketLocation() const;
	virtual int32 GetPlayerLevel() const;
	virtual void Die() = 0;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateFacingTarget(const FVector& TargetLocation) = 0;

	UFUNCTION(BlueprintCallable)
	virtual UAnimMontage* GetHitReactMontage() = 0;
};
