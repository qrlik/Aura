// Copyright by Aura

#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetDataController/AuraWidgetDataController.h"
#include "UI/WidgetDataController/OverlayWidgetDataController.h"

UOverlayWidgetDataController* UAuraAbilitySystemLibrary::GetOverlayWidgetDataController(const UObject* WorldContexObject) {
	if (auto* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContexObject, 0))) {
		if (auto* HUD = PC->GetHUD<AAuraHUD>()) {
			const FWidgetDataControllerParams Params{ PC };
			return HUD->GetOverlayWidgetDataController(Params);
		}
	}
	return nullptr;
}
