// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class IHighlightInterface;
class UInputAction;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void CursorTrace();
	void Move(const FInputActionValue& Value);

	void SetupInput();

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	TScriptInterface<IHighlightInterface> HighlightedObject;
};
