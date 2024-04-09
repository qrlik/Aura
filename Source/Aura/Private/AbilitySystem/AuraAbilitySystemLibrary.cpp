// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

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
