// Copyright by Aura

#include "UI/HUD/AuraHUD.h"

#include "UI/AuraUserWidget.h"

void AAuraHUD::BeginPlay() {
	Super::BeginPlay();

	InitOverlay();
}

void AAuraHUD::InitOverlay() {
	if (auto* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass)) {
		OverlayWidget = Widget;
		OverlayWidget->AddToViewport();
	}
}
