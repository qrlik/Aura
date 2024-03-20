// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHighlightInterface : public UInterface {
	GENERATED_BODY()
};

class AURA_API IHighlightInterface {
	GENERATED_BODY()

public:
	IHighlightInterface();

	void HighlightActor();
	void UnHighlightActor();

protected:
	virtual void InitializeHighlight();

	virtual void EnableHighlightImpl(bool State) = 0;

private:
	bool bHighlighted = false;
};
