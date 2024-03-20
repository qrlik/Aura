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
	void HighlightActor();
	void UnHighlightActor();

protected:
	virtual void HighlightActorImpl() = 0;
	virtual void UnHighlightActorImpl() = 0;

private:
	bool bHighlighted = false;
};
