// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AI/NavigationSystemBase.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "UI/WidgetDataController/OverlayWidgetDataController.h"

UOverlayWidgetDataController* UAuraAbilitySystemLibrary::GetOverlayWidgetDataController(const UObject* WorldContexObject) {
	if (const auto* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContexObject, 0))) {
		if (const auto* HUD = PC->GetHUD<AAuraHUD>()) {
			return HUD->GetOverlayWidgetDataController();
		}
	}
	return nullptr;
}

UAttributeWidgetDataController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetDataController(const UObject* WorldContexObject) {
	if (const auto* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContexObject, 0))) {
		if (const auto* HUD = PC->GetHUD<AAuraHUD>()) {
			return HUD->GetAttributeMenuWidgetDataController();
		}
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass, float Level) {
	const auto* World = AbilitySystemComponent->GetWorld();
	if (!World) {
		return;
	}
	const auto* GameMode = World->GetAuthGameMode<AAuraGameModeBase>();
	if (!GameMode) {
		return;
	}
	const auto CharacterClassInfo = GameMode->CharacterClassInfo;
	const auto& ClassDefaultInfo = CharacterClassInfo->GetClassInfo(CharacterClass);
	AbilitySystemComponent->ApplyGameplayEffectToSelf(ClassDefaultInfo.PrimaryAttributes.GetDefaultObject(), Level,
	                                                  AbilitySystemComponent->MakeEffectContext());
	AbilitySystemComponent->ApplyGameplayEffectToSelf(CharacterClassInfo->GetSecondaryAttributesClass().GetDefaultObject(), Level,
	                                                  AbilitySystemComponent->MakeEffectContext());
	AbilitySystemComponent->ApplyGameplayEffectToSelf(CharacterClassInfo->GetVitalAttributesClass().GetDefaultObject(), Level,
	                                                  AbilitySystemComponent->MakeEffectContext());
}
