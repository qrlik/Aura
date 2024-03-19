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