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

	virtual int32 GetPlayerLevel() const override;

protected:
	virtual void InitializeHighlight() override;

	virtual void EnableHighlightImpl(bool State) override;

private:
	UPROPERTY(EditAnywhere, Category = "Character Class Defaults")
	int32 Level = 1;
};
