// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetDataController.generated.h"

class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
class AAuraPlayerState;
class AAuraPlayerController;

UCLASS()
class AURA_API UAuraWidgetDataController : public UObject {
	GENERATED_BODY()

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
