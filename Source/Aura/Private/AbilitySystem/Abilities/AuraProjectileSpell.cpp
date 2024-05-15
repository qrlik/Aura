// Copyright by Aura

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation) {
	check(ProjectileClass);
	check(DamageEffectClass);
	if (!ensure(IsActive())) {
		return;
	}

	const auto& ActivationInfo = GetCurrentActivationInfoRef();
	if (!HasAuthority(&ActivationInfo)) {
		return;
	}

	auto* Owner = GetAvatarActorFromActorInfo();
	const TScriptInterface<ICombatInterface> CombatInterface = Owner;
	ensure(CombatInterface);
	if (!CombatInterface) {
		return;
	}

	const auto& SpawnLocation = CombatInterface->GetCombatSocketLocation();
	auto ProjectileRotation = (TargetLocation - SpawnLocation).Rotation();
	ProjectileRotation.Pitch = 0.0;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(ProjectileRotation.Quaternion());

	auto* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, Owner, CastChecked<APawn>(Owner),
	                                                                   ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const auto* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo_Checked();
	const auto Effect = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), AbilitySystemComponent->MakeEffectContext());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Effect, AuraGameplayTags::Get().Damage, Damage.GetValueAtLevel(GetAbilityLevel()));
	Projectile->DamageEffect = Effect;

	Projectile->FinishSpawning(SpawnTransform);
}
