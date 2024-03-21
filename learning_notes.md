# 2. Project Creation

## lesson 3. Project Creation
*Editor Preferences*\
General - Asset Editor Open Location\
General - Enable live coding\
General - Automatically Compile Newly Added C++ Classes\

*Project Settings*\
Copyright Notice\

## lesson 6. Character classes
UCLASS(Abstract) - Class is abstract and can't be instantiated directly\

## lesson 7.
*TObjectPtr*\
advanced cook-time dependency/access tracking - can track how ofter pointer accessed or dereferenced\
editor-time lazy load behaviour - asset can not be loaded until its actually needed\

## lesson 8. Template Animation BP
EventGraph -> Variable Get -> Convert to Validated Get\
Blendspace Player for template animation bp\
Asset Override in child BP (View - Asset Override Editor) -> set Blendspace for Blendspace Player\

## lesson 9. Enhanced Input
Input Action -> Input Mapping Context -> Player Mappable Input Config\
Console -> *showdebug enhancedinput* - displays the available input action and axis mappings used by your project\
Console -> *showdebug devices*\

*Injecting Input*\
Console -> *Input.+key* (key from InputCoreTypes.cpp)\
UEnhancedPlayerInput::InjectInputForAction\

## lesson 10. PlayerController
AActor::bReplicates\
APlayerController::DefaultMouseCursor\
APlayerController::GetLocalPlayer - each active player on the current client/listen server has a LocalPlayer\

ULocalPlayer::GetSubsystem\
UEnhancedInputLocalPlayerSubsystem::AddMappingContext\

FInputModeGameAndUI::SetLockMouseToViewportBehavior\
FInputModeGameAndUI::SetHideCursorDuringCapture\

## lesson 11. Movement Input
CastChecked - Cast with crash test\

FInputActionValue\
UInputAction\
UEnhancedInputComponent::BindAction\

ETriggerState - None/Ongoing/Triggered\
ETriggerEvent::Started + [ETriggerState::Triggered] -> ETriggerEvent::Ongoing + ETriggerState::Triggered -> ETriggerState::Canceled/Completed\

Project Settings -> Input -> Default Classes\

FRotationMatrix::GetUnitAxis\
FTransform::GetUnitAxis\

## lesson 12. 
Ctrl + K + O - switch between header and source files in VS\

UCharacterMovementComponent::bOrientRotationToMovement\
UCharacterMovementComponent::RotationRate\
UCharacterMovementComponent::bConstrainToPlane\
UCharacterMovementComponent::bSnapToPlaneAtStart\

USpringArmComponent::bInherit[Pitch/Yaw/Roll]\

## lesson 13. Highlight Interface
UINTERFACE\
OriginalObject->GetClass()->ImplementsInterface(UInterface::StaticClass())\
OriginalObject->Implements<UInterface>()\
Cast<IInterface>(OriginalObject)\

TScriptInterface<IMyInterface>(MyObjectPtr)\
MyScriptInterface.GetObject()\
MyScriptInterface.GetInterface()\

## lesson 14. Highlight Enemies
APlayerController::PlayerTick - processes player input\
APlayerController::GetHitResultUnderCursor\
bTraceComplex - use complex collision to provide better precision\

## lesson 15. Post Proccess Highlight
PostProcessVolume - Post Process Volume Settings - Infinite Extent (Unbound)\
*Project Settings* -> Engine -> Rendering -> Custom Depth-Stencil Pass -> Custom Depth-Stencil Pass\

UPrimitiveComponent::SetRenderCustomDepth\
UPrimitiveComponent::SetCustomDepthStencilValue\

## lesson 17. Main Parts of GAS
Ability System Component\
Attributes Set\
Gameplay Abilities -> Ability Task\
Gameplay Effects\
Gameplay Cues\
Gameplay Tags\

## lesson 18.
AActor::NetUpdateFrequency - how often considered for replication\

## lesson 22. Replication Mode
UAbilitySystemComponent::SetReplicationMode\
EGameplayEffectReplicationMode::Full - Single Player
EGameplayEffectReplicationMode::Mixed - Multiplayer, player controlled Actors
EGameplayEffectReplicationMode::Minimal - Multiplayer, AI controlled Actors

*Note*: for EGameplayEffectReplicationMode::Mixed OwnerPawn::GetOwner must return Controller.

## lesson 23. Ability Actor Info
UAbilitySystemComponent::OwnerActor\
UAbilitySystemComponent::AvatarActor\

UAbilitySystemComponent::InitAbilityActorInfo\

*Player Controller situation:*\
PossessedBy\ - AController::Possess call only with *Authority*

AcknowledgePossesion - for client if ASC on Pawn\
OnRep_PlayerState - for client if ASC on PlayerState\
*Note*: why must call InitAbilityActorInfo on client if Owner and Avatar field have replication from server?

*AI Controller situation:*\
BeginPlay - server/client if ASC on Pawn\