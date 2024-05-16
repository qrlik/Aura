// Copyright by Aura

#include "Character/AuraCharacterBase.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Aura/Aura.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacterBase::AAuraCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MotionWarping = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);
}

void AAuraCharacterBase::BeginPlay() {
	Super::BeginPlay();

	ensure(HitReactMontage);
}

void AAuraCharacterBase::InitializeDefaultAttributes() const {
	InitializeAttributesEffect(DefaultPrimaryAttributes);
	InitializeAttributesEffect(DefaultSecondaryAttributes);
	InitializeAttributesEffect(DefaultVitalAttributes);
}

void AAuraCharacterBase::OnHitReactChanged(const FGameplayTag ChangedTag, int32 NewCount) {
	if (!AllowMoveOnHitReact) {
		CachedWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		GetCharacterMovement()->MaxWalkSpeed = (NewCount > 0) ? 0.f : CachedWalkSpeed;
	}
}

void AAuraCharacterBase::OnAbilitySystemComponentReady() {
	check(AbilitySystemComponent);
	InitializeDefaultAttributes();
	AddCharacterAbilities();
	BindAbilitySystemComponentCallbacks();
}

void AAuraCharacterBase::SetAllowMoveOnHitReact(bool State) {
	AllowMoveOnHitReact = State;
}

void AAuraCharacterBase::AddCharacterAbilities() const {
	AbilitySystemComponent->AddAbilities(StartupAbilities);
}

void AAuraCharacterBase::BindAbilitySystemComponentCallbacks() {
	AbilitySystemComponent->RegisterGameplayTagEvent(AuraGameplayTags::Get().Effects_HitReact).AddUObject(this, &AAuraCharacterBase::OnHitReactChanged);
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

UAnimMontage* AAuraCharacterBase::GetHitReactMontage() {
	return HitReactMontage;
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
