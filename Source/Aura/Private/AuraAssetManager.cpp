// Copyright by Aura


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get() {
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();

	AuraGameplayTags::InitializeNativeTags();
}
