// Copyright by Aura

#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void AAuraCharacterBase::InitializePrimaryAttributes() const {
	check(AbilitySystemComponent);
	check(DefaultPrimaryAttributes);
	AbilitySystemComponent->ApplyGameplayEffectToSelf(DefaultPrimaryAttributes.GetDefaultObject(), 1.f,
	                                                  AbilitySystemComponent->MakeEffectContext());
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const {
	return AttributeSet;
}
