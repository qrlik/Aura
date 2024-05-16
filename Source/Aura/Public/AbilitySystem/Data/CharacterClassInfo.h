// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8 {
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset {
	GENERATED_BODY()

public:
	const FCharacterClassDefaultInfo& GetClassInfo(ECharacterClass Class);
	TArray<TSubclassOf<UGameplayAbility>> GetAbilitiesClasses() const;
	TSubclassOf<UGameplayEffect> GetSecondaryAttributesClass() const;
	TSubclassOf<UGameplayEffect> GetVitalAttributesClass() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> ClassesInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Common Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
};
