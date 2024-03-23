// Copyright by Aura

#include "UI/HUD/AuraHUD.h"

#include "Player/AuraPlayerController.h"
#include "UI/AuraUserWidget.h"
#include "UI/WidgetDataController/OverlayWidgetDataController.h"

UOverlayWidgetDataController* AAuraHUD::GetOverlayWidgetDataController(const FWidgetDataControllerParams& Params) {
	if (!OverlayWidgetDataController) {
		OverlayWidgetDataController = NewObject<UOverlayWidgetDataController>(this, UOverlayWidgetDataController::StaticClass());
	}
	OverlayWidgetDataController->SetWidgetDataControllerParams(Params);
	return OverlayWidgetDataController;
}

void AAuraHUD::UpdateOverlay() {
	if (OverlayWidget) {
		const FWidgetDataControllerParams Params{ Cast<AAuraPlayerController>(GetOwningPlayerController()) };
		OverlayWidget->SetWidgetDataController(GetOverlayWidgetDataController(Params));
	}
}

void AAuraHUD::BeginPlay() {
	Super::BeginPlay();

	InitOverlay();
	UpdateOverlay();
}

void AAuraHUD::InitOverlay() {
	if (!OverlayWidget) {
		checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized"));
		OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
		OverlayWidget->AddToViewport();
	}
}
