// Copyright by Aura

#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetupInput();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	auto* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
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

	auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(InputSubsystem);
	check(AuraContext);

	InputSubsystem->AddMappingContext(AuraContext, 0);
}
