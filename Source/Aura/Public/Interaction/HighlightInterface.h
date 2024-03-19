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
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
