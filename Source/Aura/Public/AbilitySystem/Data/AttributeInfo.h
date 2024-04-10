// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription;
};

UCLASS()
class AURA_API UAttributeInfo : public UDataAsset {
	GENERATED_BODY()

public:
	const TArray<FAuraAttributeInfo>& GetAttributesInformation() const;

	const FAuraAttributeInfo& FindAttributeInfoByTag(const FGameplayTag& Tag, bool bLogNotFound = false) const;
	const FAuraAttributeInfo& FindAttributeInfoByAttribute(const FGameplayAttribute& Attribute, bool bLogNotFound = false) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributesInformation;

private:
	FAuraAttributeInfo EmptyAttributeInfo;
};
