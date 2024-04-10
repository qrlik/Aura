// Copyright by Aura

#include "AbilitySystem/Data/AttributeInfo.h"

const TArray<FAuraAttributeInfo>& UAttributeInfo::GetAttributesInformation() const {
	return AttributesInformation;
}

const FAuraAttributeInfo& UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& Tag, bool bLogNotFound) const {
	for (const auto& AttributeInfo : AttributesInformation) {
		if (AttributeInfo.AttributeTag.MatchesTagExact(Tag)) {
			return AttributeInfo;
		}
	}

	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("UAttributeInfo can't find Info for AttributeTag %s"), *Tag.ToString())
	}
	return EmptyAttributeInfo;
}

const FAuraAttributeInfo& UAttributeInfo::FindAttributeInfoByAttribute(const FGameplayAttribute& Attribute, bool bLogNotFound) const {
	for (const auto& AttributeInfo : AttributesInformation) {
		if (AttributeInfo.Attribute == Attribute) {
			return AttributeInfo;
		}
	}

	if (bLogNotFound) {
		UE_LOG(LogTemp, Error, TEXT("UAttributeInfo can't find Info for Attribute %s"), *Attribute.AttributeName)
	}
	return EmptyAttributeInfo;
}
