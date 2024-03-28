// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetDataController.generated.h"

class UAuraAttributeSet;
class AAuraPlayerState;
class AAuraPlayerController;

USTRUCT(BlueprintType)
struct FWidgetDataControllerParams {
	GENERATED_BODY()

	FWidgetDataControllerParams();
	FWidgetDataControllerParams(AAuraPlayerController* PC);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AAuraPlayerController> PlayerController;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AAuraPlayerState> PlayerState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAuraAttributeSet> AttributeSet;
};

UCLASS(Abstract)
class AURA_API UAuraWidgetDataController : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetDataControllerParams(const FWidgetDataControllerParams& Params);

	void Initialize();

protected:
	template <typename ClassType>
	void BindAttributeValueChange(FGameplayAttribute Attribute, void (ClassType::*Function)(const FOnAttributeChangeData&) const);

	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	virtual void InitializeImpl();

	UPROPERTY()
	TObjectPtr<AAuraPlayerController> PlayerController;
	UPROPERTY()
	TObjectPtr<AAuraPlayerState> PlayerState;
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;
};

template <typename ClassType>
void UAuraWidgetDataController::BindAttributeValueChange(FGameplayAttribute Attribute, void (ClassType::*Function)(const FOnAttributeChangeData&) const) {
	auto& Delegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute);
	check(!Delegate.IsBoundToObject(this));
	Delegate.AddUObject(CastChecked<ClassType>(this), Function);
}
