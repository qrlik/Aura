// Copyright by Aura

#include "UI/HUD/AuraHUD.h"

#include "Player/AuraPlayerController.h"
#include "UI/AuraUserWidget.h"
#include "UI/WidgetDataController/AttributeWidgetDataController.h"
#include "UI/WidgetDataController/OverlayWidgetDataController.h"

UOverlayWidgetDataController* AAuraHUD::GetOverlayWidgetDataController() const {
	return OverlayDataController;
}

UAttributeWidgetDataController* AAuraHUD::GetAttributeMenuWidgetDataController() const {
	return AttributeMenuDataController;
}

void AAuraHUD::UpdateWidgetsDataControllers() const {
	if (!bInitialized) {
		return;
	}
	const FWidgetDataControllerParams Params{ Cast<AAuraPlayerController>(GetOwningPlayerController()) };
	OverlayDataController->SetWidgetDataControllerParams(Params);
	AttributeMenuDataController->SetWidgetDataControllerParams(Params);

	OverlayDataController->Initialize();
	AttributeMenuDataController->Initialize();
}

void AAuraHUD::BeginPlay() {
	Super::BeginPlay();

	CreateWidgetsDataControllers();
	CreateWidgets();

	Initialize();
}

void AAuraHUD::CreateWidgetsDataControllers() {
	checkf(OverlayDataControllerClass, TEXT("Overlay Data Widget Controller class uninitialized"));
	OverlayDataController = NewObject<UOverlayWidgetDataController>(this, OverlayDataControllerClass);
	checkf(AttributeMenuDataControllerClass, TEXT("Attribute Menu Widget Data Controller class uninitialized"));
	AttributeMenuDataController = NewObject<UAttributeWidgetDataController>(this, AttributeMenuDataControllerClass);
}

void AAuraHUD::CreateWidgets() {
	CreateOverlay();
}

void AAuraHUD::CreateOverlay() {
	checkf(OverlayClass, TEXT("Overlay Widget Class uninitialized"));
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayClass);
	OverlayWidget->AddToViewport();
	OverlayWidget->SetWidgetDataController(OverlayDataController);
}

void AAuraHUD::Initialize() {
	ensure(!bInitialized);
	bInitialized = true;

	UpdateWidgetsDataControllers();
}

