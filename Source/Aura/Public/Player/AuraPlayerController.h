// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UDamageTextComponent;
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

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(AActor* Target, float Damage);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void InputTagPressed(FGameplayTag Tag);
	void InputTagReleased(FGameplayTag Tag);
	void InputTagHeld(FGameplayTag Tag);

	void CursorTrace();
	void Move(const FInputActionValue& Value);
	void Shift(const FInputActionValue& Value);

	void SetupInput();
	void SetupAbilitySystemComponent();

	void CheckAutorunInput(FGameplayTag ReleasedTag);
	void ProcessAutoRun();

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	TScriptInterface<IHighlightInterface> HighlightedObject;
	FHitResult CursorHit;

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
	bool bShifting = false;
};
