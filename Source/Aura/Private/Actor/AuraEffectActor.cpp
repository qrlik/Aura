// Copyright by Aura

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor() {
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AAuraEffectActor::BeginPlay() {
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddUniqueDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                      bool bFromSweep, const FHitResult& SweepResult) {
	const TScriptInterface<IAbilitySystemInterface> AbilitySystem = OtherActor;
	if (!AbilitySystem || !AbilitySystem->GetAbilitySystemComponent()) {
		return;
	}
	// TODO: Change to Gameplay Effect. For learning purpose used const_cast
	if (const auto* AttributeSet = AbilitySystem->GetAbilitySystemComponent()->GetSet<UAuraAttributeSet>()) {
		const_cast<UAuraAttributeSet*>(AttributeSet)->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}
