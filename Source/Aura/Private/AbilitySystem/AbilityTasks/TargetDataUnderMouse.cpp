// Copyright by Aura


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility) {
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate() {
	if (IsLocallyControlled()) {
		SendMouseCursorData();
	}
	else {
	}
}

void UTargetDataUnderMouse::SendMouseCursorData() const {
	FScopedPredictionWindow ScopedPrediction{ AbilitySystemComponent.Get() };

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	auto* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetDataHandle.Add(TargetData);

	Ability->GetActorInfo().PlayerController->GetHitResultUnderCursor(ECC_Camera, false, TargetData->HitResult);
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), TargetDataHandle, FGameplayTag{},
	                                                      AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(TargetDataHandle);
	}
}
