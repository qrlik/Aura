// Copyright by Aura

#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void AAuraCharacterBase::InitializeDefaultAttributes() const {
	InitializeAttributesEffect(DefaultPrimaryAttributes);
	InitializeAttributesEffect(DefaultSecondaryAttributes);
	InitializeAttributesEffect(DefaultVitalAttributes);
}

void AAuraCharacterBase::AddCharacterAbilities() const {
	AbilitySystemComponent->AddAbilities(StartupAbilities);
}

void AAuraCharacterBase::InitializeAttributesEffect(TSubclassOf<UGameplayEffect> Effect) const {
	check(AbilitySystemComponent);
	check(Effect);
	auto EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1.f, EffectContext);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

FVector AAuraCharacterBase::GetCombatSocketLocation() const {
	check(Weapon->DoesSocketExist(WeaponSocketName));
	return Weapon->GetSocketLocation(WeaponSocketName);
}

UAuraAttributeSet* AAuraCharacterBase::GetAttributeSet() const {
	return AttributeSet;
}
