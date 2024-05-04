// Copyright by Aura

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation) {
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
	auto ProjectileRotation = (TargetLocation - SpawnLocation).ToOrientationQuat();
	ProjectileRotation.Y = 0.0;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(ProjectileRotation);

	auto* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, Owner, CastChecked<APawn>(Owner),
	                                                                   ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(SpawnTransform);
}