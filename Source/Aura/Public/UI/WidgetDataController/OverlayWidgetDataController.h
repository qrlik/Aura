// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "OverlayWidgetDataController.generated.h"

struct FOnAttributeChangeData;
class UAuraUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

USTRUCT(BlueprintType)
struct FMessageWidgetByTagRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Text;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UAuraUserWidget> Widget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTexture2D> Image;
};

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetDataController : public UAuraWidgetDataController {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

protected:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetByTag;
};
