// Copyright by Aura

#include "Interaction/HighlightInterface.h"

IHighlightInterface::IHighlightInterface() {
	InitializeHighlight();
}

void IHighlightInterface::InitializeHighlight() {
}

void IHighlightInterface::HighlightActor() {
	if (!bHighlighted) {
		bHighlighted = true;
		EnableHighlightImpl(true);
	}
}

void IHighlightInterface::UnHighlightActor() {
	if (bHighlighted) {
		bHighlighted = false;
		EnableHighlightImpl(false);
	}
}
