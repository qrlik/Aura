// Copyright by Aura

#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/InputComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/HighlightInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	CursorTrace();
	Super::PlayerTick(DeltaTime);

	ProcessAutoRun();
}

void AAuraPlayerController::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	SetupAbilitySystemComponent();
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetupInput();
	SetupAbilitySystemComponent();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	auto* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::Shift);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::Shift);
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
	if (AbilitySystemComponent) {
		AbilitySystemComponent->AbilityInputTagReleased(Tag);
	}
	CheckAutorunInput(Tag);
}

void AAuraPlayerController::InputTagHeld(FGameplayTag Tag) {
	if (Tag.MatchesTagExact(AuraGameplayTags::Get().Input_LMB)) {
		if (bTargeting || bShifting) {
			if (AbilitySystemComponent) {
				AbilitySystemComponent->AbilityInputTagHeld(Tag);
			}
		}
		else {
			FollowTime += GetWorld()->GetDeltaSeconds();
			if (CursorHit.bBlockingHit) {
				CachedDestination = CursorHit.ImpactPoint;
			}
			if (auto* ControlledPawn = GetPawn()) {
				const auto MoveDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(MoveDirection);
			}
		}
	}
	else if (AbilitySystemComponent) {
		AbilitySystemComponent->AbilityInputTagHeld(Tag);
	}
}

void AAuraPlayerController::CursorTrace() {
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) {
		return;
	}

	const TScriptInterface<IHighlightInterface> HighlightCandidate = CursorHit.GetActor();
	if (HighlightCandidate != HighlightedObject) {
		if (HighlightedObject) {
			HighlightedObject->UnHighlightActor();
		}
		if (HighlightCandidate) {
			HighlightCandidate->HighlightActor();
		}
		HighlightedObject = HighlightCandidate;
	}
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

void AAuraPlayerController::Shift(const FInputActionValue& Value) {
	bShifting = Value.Get<bool>();
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
	if (const auto* State = GetPlayerState<AAuraPlayerState>()) {
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(State->GetAbilitySystemComponent());
	}
}

void AAuraPlayerController::CheckAutorunInput(FGameplayTag ReleasedTag) {
	if (!ReleasedTag.MatchesTagExact(AuraGameplayTags::Get().Input_LMB)) {
		return;
	}

	const auto* ControlledPawn = GetPawn();
	const auto IsShortClick = FollowTime < ShortPressThreshold || FMath::IsNearlyEqual(FollowTime, ShortPressThreshold);
	FollowTime = 0.f;
	if (bTargeting || bShifting || !IsShortClick || !ControlledPawn) {
		return;
	}

	auto* Path = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination);
	if (!Path) {
		return;
	}

	Spline->ClearSplinePoints();
	for (const auto& PathPoint : Path->PathPoints) {
		Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World, false);
	}
	if (!Path->PathPoints.IsEmpty()) {
		CachedDestination = Path->PathPoints.Last();
	}
	Spline->UpdateSpline();
	bAutoRunning = true;
}

void AAuraPlayerController::ProcessAutoRun() {
	auto* ControllerPawn = GetPawn();
	if (!ControllerPawn || !bAutoRunning) {
		return;
	}
	const auto SplinePoint = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	const auto Direction = Spline->FindDirectionClosestToWorldLocation(SplinePoint, ESplineCoordinateSpace::World);
	ControllerPawn->AddMovementInput(Direction);

	const auto DistanceToDestination = (SplinePoint - CachedDestination).Length();
	bAutoRunning = DistanceToDestination > AutoRunAcceptanceRadius;
}
