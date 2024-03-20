// Copyright by Aura

#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

void AAuraEnemy::InitializeHighlight() {
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::EnableHighlightImpl(bool State) {
	GetMesh()->SetRenderCustomDepth(State);
	Weapon->SetRenderCustomDepth(State);
}
