// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeWidgetDataController;
class UOverlayWidgetDataController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetDataController")
	static UOverlayWidgetDataController* GetOverlayWidgetDataController(const UObject* WorldContexObject);
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetDataController")
	static UAttributeWidgetDataController* GetAttributeMenuWidgetDataController(const UObject* WorldContexObject);
};
