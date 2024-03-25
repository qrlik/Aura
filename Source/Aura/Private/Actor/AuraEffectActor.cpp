// Copyright by Aura

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor() {
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor) {
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor) {
}

void AAuraEffectActor::ApplyInstantEffectToTarget(AActor* TargetActor) const {
	ApplyEffectToTarget(TargetActor, InstantGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyDurationEffectToTarget(AActor* TargetActor) const {
	ApplyEffectToTarget(TargetActor, DurationGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyInfiniteEffectToTarget(AActor* TargetActor) const {
	ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect.GameplayEffectClass);
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass) const {
	auto* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!AbilitySystemComponent) {
		return;
	}
	check(EffectClass);

	auto EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto EffectSpec = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1.f, EffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}
