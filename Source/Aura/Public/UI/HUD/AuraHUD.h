// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetDataControllerParams;
class UAuraUserWidget;
class UOverlayWidgetDataController;

UCLASS()
class AURA_API AAuraHUD : public AHUD {
	GENERATED_BODY()

public:
	UOverlayWidgetDataController* GetOverlayWidgetDataController(const FWidgetDataControllerParams& Params);

	void UpdateOverlay();

protected:
	virtual void BeginPlay() override;

private:
	void InitOverlay();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetDataController> OverlayWidgetDataControllerClass;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetDataController> OverlayWidgetDataController;
};
