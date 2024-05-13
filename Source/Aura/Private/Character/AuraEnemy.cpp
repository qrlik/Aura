// Copyright by Aura

#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/AuraUserWidget.h"
#include "UI/WidgetDataController/EnemyWidgetDataController.h"

AAuraEnemy::AAuraEnemy() {
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(GetRootComponent());
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawAtDesiredSize(true);
}

int32 AAuraEnemy::GetPlayerLevel() const {
	return Level;
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();

	CreateWidgetDataController();

	InitializeDefaultAttributes();
	InitializeWidget();
}

void AAuraEnemy::InitializeDefaultAttributes() const {
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(AbilitySystemComponent, CharacterClass, Level);
}

void AAuraEnemy::InitializeHighlight() {
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::EnableHighlightImpl(bool State) {
	GetMesh()->SetRenderCustomDepth(State);
	Weapon->SetRenderCustomDepth(State);
}

void AAuraEnemy::CreateWidgetDataController() {
	WidgetDataController = NewObject<UEnemyWidgetDataController>(this);
}

void AAuraEnemy::InitializeWidget() const {
	auto* Widget = CastChecked<UAuraUserWidget>(WidgetComponent->GetWidget());
	Widget->SetWidgetDataController(WidgetDataController);

	FWidgetDataControllerParams Params;
	Params.AbilitySystemComponent = AbilitySystemComponent;
	Params.AttributeSet = AttributeSet;
	WidgetDataController->SetWidgetDataControllerParams(Params);
	WidgetDataController->Initialize();
}
