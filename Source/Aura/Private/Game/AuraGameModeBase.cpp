// Copyright by Aura


#include "Game/AuraGameModeBase.h"

void AAuraGameModeBase::BeginPlay() {
	Super::BeginPlay();
	check(CharacterClassInfo);
}
