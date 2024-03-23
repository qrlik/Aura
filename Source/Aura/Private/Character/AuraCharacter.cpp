// Copyright by Aura

#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter() {
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) {
	Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);
	if (NewPlayerState == OldPlayerState) {
		return;
	}
	UpdateGameplayAbilities();
	UpdateHUD();
}

void AAuraCharacter::UpdateGameplayAbilities() {
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetAvatarActor(nullptr);
	}

	if (const auto* State = GetPlayerState<AAuraPlayerState>()) {
		AbilitySystemComponent = State->GetAbilitySystemComponent();
		AbilitySystemComponent->SetAvatarActor(this);
		AttributeSet = State->GetAttributeSet();
	}
	else {
		AbilitySystemComponent = nullptr;
		AttributeSet = nullptr;
	}
}

void AAuraCharacter::UpdateHUD() const {
	if (!GetPlayerState<AAuraPlayerState>()) {
		return;
	}
	if (const auto* PlayerController = GetController<AAuraPlayerController>()) {
		if (auto* HUD = PlayerController->GetHUD<AAuraHUD>()) {
			HUD->UpdateOverlay();
		}
	}
}
