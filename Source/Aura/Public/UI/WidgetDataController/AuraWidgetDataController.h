// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetDataController.generated.h"

class UAuraAbilitySystemComponent;
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

UCLASS()
class AURA_API UAuraWidgetDataController : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetDataControllerParams(const FWidgetDataControllerParams& Params);

private:
	UPROPERTY()
	TObjectPtr<AAuraPlayerController> PlayerController;
	UPROPERTY()
	TObjectPtr<AAuraPlayerState> PlayerState;
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;
};
