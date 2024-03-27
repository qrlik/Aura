// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface {
	GENERATED_BODY()

public:
	AAuraEnemy();

protected:
	virtual void InitializeHighlight() override;

	virtual void EnableHighlightImpl(bool State) override;
};
