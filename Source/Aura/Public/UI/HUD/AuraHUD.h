// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetDataControllerParams;
class UAuraUserWidget;
class UAttributeWidgetDataController;
class UOverlayWidgetDataController;

UCLASS()
class AURA_API AAuraHUD : public AHUD {
	GENERATED_BODY()

public:
	UOverlayWidgetDataController* GetOverlayWidgetDataController() const;
	UAttributeWidgetDataController* GetAttributeMenuWidgetDataController() const;

	void UpdateWidgetsDataControllers() const;

protected:
	virtual void BeginPlay() override;

private:
	void CreateOverlay();
	void CreateWidgets();
	void CreateWidgetsDataControllers();

	void Initialize();

	UPROPERTY(EditDefaultsOnly, Category = "HUD|Data Controllers")
	TSubclassOf<UOverlayWidgetDataController> OverlayDataControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "HUD|Data Controllers")
	TSubclassOf<UAttributeWidgetDataController> AttributeMenuDataControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UAuraUserWidget> OverlayClass;

	UPROPERTY()
	TObjectPtr<UAttributeWidgetDataController> AttributeMenuDataController;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetDataController> OverlayDataController;
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	bool bInitialized = false;
};
