// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface {
	GENERATED_BODY()

protected:
	virtual void HighlightActorImpl() override;
	virtual void UnHighlightActorImpl() override;
};
