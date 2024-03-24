// Copyright by Aura

#include "UI/HUD/AuraHUD.h"

#include "Player/AuraPlayerController.h"
#include "UI/AuraUserWidget.h"
#include "UI/WidgetDataController/OverlayWidgetDataController.h"

UOverlayWidgetDataController* AAuraHUD::GetOverlayWidgetDataController(const FWidgetDataControllerParams& Params) {
	if (!OverlayWidgetDataController) {
		checkf(OverlayWidgetDataControllerClass, TEXT("Overlay Widget Data Controller Class uninitialized"));
		OverlayWidgetDataController = NewObject<UOverlayWidgetDataController>(this, OverlayWidgetDataControllerClass);
	}
	OverlayWidgetDataController->SetWidgetDataControllerParams(Params);
	return OverlayWidgetDataController;
}

void AAuraHUD::UpdateOverlay() {
	if (!OverlayWidget) {
		return;
	}
	const FWidgetDataControllerParams Params{ Cast<AAuraPlayerController>(GetOwningPlayerController()) };
	auto* WidgetDataController = GetOverlayWidgetDataController(Params);

	OverlayWidget->SetWidgetDataController(WidgetDataController);
	WidgetDataController->Initialize();
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
