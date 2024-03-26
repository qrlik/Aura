// Copyright by Aura

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor() {
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor) {
	auto* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!AbilitySystemComponent) {
		return;
	}

	for (const auto& EffectData : Effects) {
		if (EffectData.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
			ApplyEffectToTarget(AbilitySystemComponent, EffectData);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor) {
	auto* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!AbilitySystemComponent) {
		return;
	}

	for (const auto& EffectData : Effects) {
		if (EffectData.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
			ApplyEffectToTarget(AbilitySystemComponent, EffectData);
		}

		if (EffectData.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
			RemoveEffectFromTarget(AbilitySystemComponent, EffectData);
		}
		check(ActiveEffects.Find(AbilitySystemComponent) == nullptr); // empty after all EEffectRemovalPolicy
	}
}

void AAuraEffectActor::ApplyEffectToTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectData& Effect) {
	if (!AbilitySystemComponent) {
		return;
	}
	check(Effect.GameplayEffectClass);

	auto EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(Effect.GameplayEffectClass, Effect.EffectLevel, EffectContext);
	const auto ActiveEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());

	if (ActiveEffect.WasSuccessfullyApplied() && Effect.ActorDestroyPolicy == EEffectActorDestroyPolicy::DestroyOnApply) {
		Destroy();
	}
	else if (ActiveEffect.IsValid() && Effect.RemovalPolicy != EEffectRemovalPolicy::DoNotRemove) {
		auto& ComponentEffects = ActiveEffects.FindOrAdd(AbilitySystemComponent, {});
		ComponentEffects.Emplace(Effect.GameplayEffectClass, ActiveEffect);
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectData& Effect) {
	if (!AbilitySystemComponent) {
		return;
	}
	auto* EffectsByComponent = ActiveEffects.Find(AbilitySystemComponent);
	if (!EffectsByComponent) {
		return;
	}

	EffectsByComponent->RemoveAllSwap([AbilitySystemComponent, EffectClass = Effect.GameplayEffectClass](const auto& ActiveEffectData) {
		if (EffectClass != ActiveEffectData.GameplayEffectClass) {
			return false;
		}
		AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectData.Handle, 1);
		return true;
	});

	if (Effect.ActorDestroyPolicy == EEffectActorDestroyPolicy::DestroyOnRemove) {
		Destroy();
	}
	if (EffectsByComponent->IsEmpty()) {
		ActiveEffects.Remove(AbilitySystemComponent);
	}
}
