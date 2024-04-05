// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "AttributeWidgetDataController.generated.h"

UCLASS()
class AURA_API UAttributeWidgetDataController : public UAuraWidgetDataController {
	GENERATED_BODY()

protected:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
