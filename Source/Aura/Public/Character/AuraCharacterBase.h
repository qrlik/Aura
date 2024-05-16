// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

struct FGameplayTag;
class UGameplayAbility;
class UGameplayEffect;
class UMotionWarpingComponent;
class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface {
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAnimMontage* GetHitReactMontage() override;
	virtual FVector GetCombatSocketLocation() const override;

	virtual void UpdateFacingTarget(const FVector& TargetLocation) override;

	UAuraAttributeSet* GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;

	virtual void AddCharacterAbilities() const;
	virtual void InitializeDefaultAttributes() const;
	virtual void OnHitReactChanged(const FGameplayTag ChangedTag, int32 NewCount);

	void OnAbilitySystemComponentReady();
	void SetAllowMoveOnHitReact(bool State);

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UMotionWarpingComponent> MotionWarping;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

private:
	void BindAbilitySystemComponentCallbacks();

	void InitializeAttributesEffect(TSubclassOf<UGameplayEffect> Effect) const;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName TargetWarpingName;

	float CachedWalkSpeed = 0.f;
	bool AllowMoveOnHitReact = true;
};
