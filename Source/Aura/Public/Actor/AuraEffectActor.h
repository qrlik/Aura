// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy {
	DoNotApply,
	ApplyOnOverlap,
	ApplyOnEndOverlap
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy {
	DoNotRemove,
	RemoveOnEndOverlap
};

UENUM(BlueprintType)
enum class EEffectActorDestroyPolicy {
	DoNotDestroy,
	DestroyOnApply,
	DestroyOnRemove
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EEffectActorDestroyPolicy ActorDestroyPolicy = EEffectActorDestroyPolicy::DoNotDestroy;
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Applied Effects")
	TArray<FGameplayEffectData> Effects;

private:
	void ApplyEffectToTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectData& Effect);
	void RemoveEffectFromTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectData& Effect);

	struct FActiveGameplayEffectData {
		TSubclassOf<UGameplayEffect> GameplayEffectClass;
		FActiveGameplayEffectHandle Handle;
	};

	TMap<TWeakObjectPtr<UAbilitySystemComponent>, TArray<FActiveGameplayEffectData>> ActiveEffects;
};
