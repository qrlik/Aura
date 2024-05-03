// Copyright by Aura

#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::SpawnProjectile() {
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

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	auto* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, Owner, CastChecked<APawn>(Owner),
	                                                                   ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(SpawnTransform);
}
