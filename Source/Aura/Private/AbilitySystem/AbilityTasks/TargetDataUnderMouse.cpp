// Copyright by Aura


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility) {
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate() {
	FHitResult HitResult;
	Ability->GetActorInfo().PlayerController->GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (HitResult.bBlockingHit) {
		ValidData.Broadcast(HitResult.ImpactPoint);
	}
}
