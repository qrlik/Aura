// Copyright by Aura

#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

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
	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetAvatarActor(nullptr);
	}

	if (!NewPlayerState) {
		AbilitySystemComponent = nullptr;
		AttributeSet = nullptr;
	}
	else if (const auto* AuraPlayerState = Cast<AAuraPlayerState>(NewPlayerState)) {
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AbilitySystemComponent->SetAvatarActor(this);
		AttributeSet = AuraPlayerState->GetAttributeSet();
	}
}
