// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "EnemyWidgetDataController.generated.h"

UCLASS()
class AURA_API UEnemyWidgetDataController : public UAuraWidgetDataController {
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BindCallbacksToDependencies() override;

private:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
