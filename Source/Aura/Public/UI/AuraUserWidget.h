// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UAuraWidgetDataController;

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetDataController(UAuraWidgetDataController* Controller);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetDataControllerSet();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraWidgetDataController> WidgetDataController;
};
