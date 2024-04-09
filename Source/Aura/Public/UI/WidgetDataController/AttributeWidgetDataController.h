// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "AttributeWidgetDataController.generated.h"

struct FAuraAttributeInfo;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

UCLASS()
class AURA_API UAttributeWidgetDataController : public UAuraWidgetDataController {
	GENERATED_BODY()

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInformation;
};
