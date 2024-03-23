// Copyright by Aura


#include "UI/WidgetDataController/AuraWidgetDataController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

FWidgetDataControllerParams::FWidgetDataControllerParams() {
}

FWidgetDataControllerParams::FWidgetDataControllerParams(AAuraPlayerController* PC):
	PlayerController(PC) {
	PlayerState = (PlayerController) ? PlayerController->GetPlayerState<AAuraPlayerState>() : nullptr;
	AbilitySystemComponent = (PlayerState) ? Cast<UAuraAbilitySystemComponent>(PlayerState->GetAbilitySystemComponent()) : nullptr;
	AttributeSet = (PlayerState) ? Cast<UAuraAttributeSet>(PlayerState->GetAttributeSet()) : nullptr;
}

void UAuraWidgetDataController::SetWidgetDataControllerParams(const FWidgetDataControllerParams& Params) {
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}

void UAuraWidgetDataController::Initialize() {
	BindCallbacksToDependencies();
	BroadcastInitialValues();
}

void UAuraWidgetDataController::BroadcastInitialValues() {
}

void UAuraWidgetDataController::BindCallbacksToDependencies() {
}
