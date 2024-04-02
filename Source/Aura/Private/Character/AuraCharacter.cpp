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

int32 AAuraCharacter::GetPlayerLevel() const {
	if (const auto* State = GetPlayerState<AAuraPlayerState>()) {
		return State->GetPlayerLevel();
	}
	return 0;
}

void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	UpdateAbilitySystemComponent();
	InitializeDefaultAttributes();

	UpdateHUD();
}

void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	UpdateAbilitySystemComponent();
	UpdateHUD();
}

void AAuraCharacter::UpdateAbilitySystemComponent() {
	const auto* State = GetPlayerState<AAuraPlayerState>();

	AbilitySystemComponent = (State) ? State->GetAbilitySystemComponent() : nullptr;
	AttributeSet = (State) ? State->GetAttributeSet() : nullptr;

	if (AbilitySystemComponent) {
		AbilitySystemComponent->SetAvatarActor(this);
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
