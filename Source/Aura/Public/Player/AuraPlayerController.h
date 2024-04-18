// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

struct FGameplayTag;
struct FInputActionValue;
class IHighlightInterface;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
class UInputAction;
class UInputMappingContext;
class USplineComponent;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void InputTagPressed(FGameplayTag Tag);
	void InputTagReleased(FGameplayTag Tag);
	void InputTagHeld(FGameplayTag Tag);

	void CursorTrace();
	void Move(const FInputActionValue& Value);

	void SetupInput();
	void SetupAbilitySystemComponent();

	void ProcessAutoRun();

private:
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	TScriptInterface<IHighlightInterface> HighlightedObject;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	FVector CachedDestination = FVector::ZeroVector;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(EditDefaultsOnly)
	float ShortPressThreshold = 0.5f;
	float FollowTime = 0.f;
	bool bAutoRunning = false;
	bool bTargeting = false;
};
