// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "OverlayWidgetDataController.generated.h"

struct FOnAttributeChangeData;
class UAuraUserWidget;

/* Struct for learn data table purpose.
 * Better struct is UUserWidget (UEffectMessageWidget) on Overlay.
 * It listens applied tags from data controller and create what it needs.
 * Right now WidgetDataController have UserWidget data that is incorrect by this data model*/
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectTagAppliedToSelfSignature, const FMessageWidgetByTagRow&, Row);

UCLASS()
class AURA_API UOverlayWidgetDataController : public UAuraWidgetDataController {
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Tags")
	FOnEffectTagAppliedToSelfSignature OnEffectMessageTagAppliedToSelf;

protected:
	virtual void BindCallbacksToDependencies() override;
	virtual void InitializeImpl() override;

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	void EffectAppliedToSelf(const FGameplayTagContainer& EffectTags) const;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetByTag;

private:
	bool CheckMessageTag(const FGameplayTag& Tag) const;
};
