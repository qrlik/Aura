// Copyright by Aura

#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& Tag, bool bLogNotFound) const {
	for (const auto& AttributeInfo : AttributesInformation) {
		if (AttributeInfo.AttributeTag.MatchesTagExact(Tag)) {
			return AttributeInfo;
		}
	}

	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("UAttributeInfo can't find Info for AttributeTag %s"), *Tag.ToString())
	}
	return FAuraAttributeInfo{};
}
