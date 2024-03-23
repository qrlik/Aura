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

	const auto* State = GetPlayerState();
	if (!State) {
		AbilitySystemComponent = nullptr;
		AttributeSet = nullptr;
	}
	else if (const auto* AuraPlayerState = Cast<AAuraPlayerState>(State)) {
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->SetAvatarActor(this);
		AttributeSet = AuraPlayerState->GetAttributeSet();
	}
}

void AAuraCharacter::UpdateHUD() const {
	if (const auto* PlayerController = GetController<AAuraPlayerController>()) {
		if (auto* HUD = PlayerController->GetHUD<AAuraHUD>()) {
			HUD->UpdateOverlay();
		}
	}
}
