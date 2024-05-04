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
		const auto AbilitySpec = GetAbilitySpecHandle();
		const auto ActivationKey = GetActivationPredictionKey();
		auto& Delegate = AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpec, ActivationKey);
		ensure(!Delegate.IsBoundToObject(this));
		Delegate.AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(AbilitySpec, ActivationKey)) {
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData() const {
	FScopedPredictionWindow ScopedPrediction{ AbilitySystemComponent.Get() };

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	auto* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetDataHandle.Add(TargetData);

	Ability->GetActorInfo().PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TargetData->HitResult);
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), TargetDataHandle, FGameplayTag{},
	                                                      AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetData, FGameplayTag Tag) const {
	AbilitySystemComponent.Get()->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(TargetData);
	}
}
