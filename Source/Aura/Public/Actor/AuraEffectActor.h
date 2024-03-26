// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy {
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy {
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FGameplayEffectData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor {
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyInstantEffectToTarget(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyDurationEffectToTarget(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyInfiniteEffectToTarget(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Applied Effects")
	FGameplayEffectData InstantGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Applied Effects")
	FGameplayEffectData DurationGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Applied Effects")
	FGameplayEffectData InfiniteGameplayEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Applied Effects")
	bool DestroyOnEffectRemoval = false;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffects;
};
