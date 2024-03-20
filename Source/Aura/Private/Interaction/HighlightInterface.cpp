// Copyright by Aura

#include "Interaction/HighlightInterface.h"

void IHighlightInterface::HighlightActor() {
	if (!bHighlighted) {
		bHighlighted = true;
		HighlightActorImpl();
	}
}

void IHighlightInterface::UnHighlightActor() {
	if (bHighlighted) {
		bHighlighted = false;
		UnHighlightActorImpl();
	}
}
