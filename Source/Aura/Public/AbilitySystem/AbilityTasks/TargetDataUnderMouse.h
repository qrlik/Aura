// Copyright by Aura

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);

UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

protected:
	virtual void Activate() override;

private:
	void SendMouseCursorData() const;

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetData, FGameplayTag Tag) const;
};
