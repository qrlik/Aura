// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;

UCLASS()
class AURA_API AAuraHUD : public AHUD {
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void InitOverlay();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
};
