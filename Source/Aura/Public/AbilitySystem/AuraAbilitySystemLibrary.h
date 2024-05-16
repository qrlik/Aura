// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeWidgetDataController;
class UOverlayWidgetDataController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetDataController")
	static UOverlayWidgetDataController* GetOverlayWidgetDataController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetDataController")
	static UAttributeWidgetDataController* GetAttributeMenuWidgetDataController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass,
	                                        float Level);

	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAbilities(UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass);
};
