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
	if (InstantGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyInstantEffectToTarget(TargetActor);
	}
	if (DurationGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyDurationEffectToTarget(TargetActor);
	}
	if (InfiniteGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap) {
		ApplyInfiniteEffectToTarget(TargetActor);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor) {
	if (InstantGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyInstantEffectToTarget(TargetActor);
	}
	if (InstantGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyDurationEffectToTarget(TargetActor);
	}
	if (InfiniteGameplayEffect.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		ApplyInfiniteEffectToTarget(TargetActor);
	}
	if (InfiniteGameplayEffect.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		auto* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
		if (!AbilitySystemComponent) {
			return;
		}

		FActiveGameplayEffectHandle EffectForRemove;
		for (const auto& [ActiveEffect, Component] : ActiveEffects) {
			if (AbilitySystemComponent == Component) {
				AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffect, 1);
				EffectForRemove = ActiveEffect;
				break;
			}
		}
		ActiveEffects.FindAndRemoveChecked(EffectForRemove);
	}
}

void AAuraEffectActor::ApplyInstantEffectToTarget(AActor* TargetActor) {
	ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyDurationEffectToTarget(AActor* TargetActor) {
	ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyInfiniteEffectToTarget(AActor* TargetActor) {
	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass) {
	auto* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	if (!AbilitySystemComponent) {
		return;
	}
	check(EffectClass);

	auto EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1.f, EffectContext);
	const auto ActiveEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());

	if (EffectClass->GetDefaultObject<UGameplayEffect>()->DurationPolicy == EGameplayEffectDurationType::Infinite
		&& InfiniteGameplayEffect.RemovalPolicy != EEffectRemovalPolicy::DoNotRemove) {
		ActiveEffects.Add(ActiveEffect, AbilitySystemComponent); // to do refactor this shared ptrs
	}

}
