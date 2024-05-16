// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

enum class ECharacterClass : uint8;
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

	virtual void AddCharacterAbilities() const override;
	virtual void Die() override;
	virtual void InitializeDefaultAttributes() const override;
	virtual void InitializeHighlight() override;

	virtual void EnableHighlightImpl(bool State) override;

private:
	void CreateWidgetDataController();

	void InitializeWidget() const;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	UPROPERTY()
	TObjectPtr<UEnemyWidgetDataController> WidgetDataController;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
};
