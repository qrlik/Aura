// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase {
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;

private:
	void UpdateGameplayAbilities();
	void UpdateHUD() const;
};
