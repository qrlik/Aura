// Copyright by Aura

#include "Character/AuraCharacterBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Aura/Aura.h"

AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
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

void AAuraCharacterBase::UpdateFacingTarget(const FVector& TargetLocation) {
	check(TargetWarpingName.IsValid());
	MotionWarping->AddOrUpdateWarpTargetFromLocation(TargetWarpingName, TargetLocation);
}

UAuraAttributeSet* AAuraCharacterBase::GetAttributeSet() const {
	return AttributeSet;
}
