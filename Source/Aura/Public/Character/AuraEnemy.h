// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

class UEnemyWidgetDataController;
class UWidgetComponent;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface {
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual int32 GetPlayerLevel() const override;

protected:
	virtual void BeginPlay() override;

	virtual void InitializeHighlight() override;

	virtual void EnableHighlightImpl(bool State) override;

private:
	void CreateWidgetDataController();

	void InitializeWidget() const;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	UPROPERTY()
	TObjectPtr<UEnemyWidgetDataController> WidgetDataController;

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults")
	int32 Level = 1;
};
