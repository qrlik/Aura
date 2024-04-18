// Copyright by Aura

#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/InputComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/HighlightInterface.h"
#include "Kismet/GameplayStatics.h"

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	CursorTrace();
	Super::PlayerTick(DeltaTime);
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetupInput();
	SetupAbilitySystemComponent();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	auto* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindInputActionsToTags(InputConfig, this, &ThisClass::InputTagPressed, &ThisClass::InputTagReleased,
	                                           &ThisClass::InputTagHeld);
}

void AAuraPlayerController::InputTagPressed(FGameplayTag Tag) {
	if (Tag.MatchesTagExact(AuraGameplayTags::Get().Input_LMB)) {
		bTargeting = static_cast<bool>(HighlightedObject);
		bAutoRunning = false;
	}
}

void AAuraPlayerController::InputTagReleased(FGameplayTag Tag) {
	AbilitySystemComponent->AbilityInputTagReleased(Tag);
}

void AAuraPlayerController::InputTagHeld(FGameplayTag Tag) {
	if (Tag.MatchesTagExact(AuraGameplayTags::Get().Input_LMB)) {
		if (bTargeting) {
			AbilitySystemComponent->AbilityInputTagHeld(Tag);
		}
		else {
			FollowTime += GetWorld()->GetDeltaSeconds();
			FHitResult CursorHit;
			if (GetHitResultUnderCursor(ECC_Camera, false, CursorHit)) {
				CachedDestination = CursorHit.ImpactPoint;
			}
			if (auto* ControlledPawn = GetPawn()) {
				const auto MoveDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(MoveDirection);
			}
		}
	}
	else {
		AbilitySystemComponent->AbilityInputTagHeld(Tag);
	}
}

void AAuraPlayerController::CursorTrace() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Camera, false, CursorHit);
	if (!CursorHit.bBlockingHit) {
		return;
	}

	const TScriptInterface<IHighlightInterface> HighlightCandidate = CursorHit.GetActor();
	if (HighlightCandidate) {
		HighlightCandidate.GetInterface()->HighlightActor();
		if (HighlightedObject && HighlightCandidate != HighlightedObject) {
			HighlightedObject.GetInterface()->UnHighlightActor();
		}
	}
	else if (HighlightedObject) {
		HighlightedObject.GetInterface()->UnHighlightActor();
	}
	HighlightedObject = HighlightCandidate;
}

void AAuraPlayerController::Move(const FInputActionValue& Value) {
	auto* ControlledPawn = GetPawn();
	if (!ControlledPawn) {
		return;
	}

	const FVector2D AxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, AxisVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, AxisVector.X);
}

void AAuraPlayerController::SetupInput() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		check(AuraContext);
		InputSubsystem->AddMappingContext(AuraContext, 0);
	}
}

void AAuraPlayerController::SetupAbilitySystemComponent() {
	AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	check(AbilitySystemComponent);
}
