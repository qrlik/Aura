# 2. Project Creation

## lesson 3. Project Creation
*Editor Preferences*\
General - Asset Editor Open Location\
General - Enable live coding\
General - Automatically Compile Newly Added C++ Classes\

*Project Settings*\
Copyright Notice\

## lesson 6. Character classes
UCLASS(*Abstract*) - Class is abstract and can't be instantiated directly\

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

<br><br>

# 3. Intro to the Gameplay Ability System

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
EGameplayEffectReplicationMode::Full - Single Player. GameplayEffect, GameplayTags, GameplayCues\
EGameplayEffectReplicationMode::Mixed - Multiplayer, player controlled Actors. GameplayEffects(AutonomousProxy/Authority), GameplayTags, GameplayCues\
EGameplayEffectReplicationMode::Minimal - Multiplayer, AI controlled Actors. GameplayTags, GameplayCues\

*Note*: for EGameplayEffectReplicationMode::Mixed OwnerPawn::GetOwner must return Controller.\

## lesson 23. Ability Actor Info
UAbilitySystemComponent::OwnerActor\
UAbilitySystemComponent::AvatarActor\

UAbilitySystemComponent::InitAbilityActorInfo\

*Player Controller situation:*\
PossessedBy\ - AController::Possess call only with *Authority*

AcknowledgePossesion - for client if ASC on Pawn\
OnRep_PlayerState - for client if ASC on PlayerState\
*Note*: why must call InitAbilityActorInfo on client if Owner and Avatar field have replication from server?\

*AI Controller situation:*\
BeginPlay - server/client if ASC on Pawn\

<br><br>

# 4. Attributes

## lesson 24. Attributes
FGameplayAttributeData -> UAttributeSet -> UAbilitySystemComponent\
GameplayEffect -> Attribute change -> Prediction (client did, server can roll back)\
Min/Max Attributes Values should be also have separate FGameplayAttributeData\

## lesson 25. Attributes Add
UPROPERTY(*ReplicatedUsing* = OnRep_[PropertyName])\

UFUNCTION()\
void OnRep_[PropertyName]([const PropertyType& OldValue]);\

*GAMEPLAYATTRIBUTE_REPNOTIFY(AttributeSetClassType, PropertyName, OldValue);*\
This is a helper macro that can be used in RepNotify functions to handle attributes that will be predictively modified by clients.\
*Note*: Is this help with server rollback?\

UObject::GetLifetimeReplicatedProps\
DOREPLIFETIME[_CONDITION][_NOTIFY](Class, Var, [ConditionType], [NotifyType])\

**ELifetimeCondition**
*COND_InitialOnly* - only once on the initial on client\
*COND_OwnerOnly* - only send to the actor's owner\
*COND_SkipOwner* - send to every connection EXCEPT the owner\
*COND_SimulatedOnly* - send only to simulated actors\
*COND_AutonomousOnly* - send only to autonomous actors\
*COND_SimulatedOrPhysics* - send to simulated or bRepPhysics actors\
*COND_InitialOrOwner*\
*COND_Custom* - no particular condition, but wants the ability to toggle on/off via SetCustomIsActiveOverride\
*COND_ReplayOnly* - This property will only send to the replay connection\
*COND_ReplayOrOwner*\
*COND_SimulatedOnlyNoReplay*\
*COND_SimulatedOrPhysicsNoReplay*\
*COND_SkipReplay* - not send to the replay connection\
*COND_Dynamic* - override the condition at runtime. Defaults to always replicate until you override it to a new condition.\
*COND_Never* - will never be replicated\
*COND_NetGroup* - replicate to connections that are part of the same group the subobject is registered to. Not usable on properties.\

*Note*: actor owner mean only authority or also autonomous? what benefit from replication only to authority on server?\

**ELifetimeRepNotifyCondition**\
*REPNOTIFY_OnChanged* - default\
*REPNOTIFY_Always*\

## lesson 26. Attributes Accessors
Ctrl + M + A/L/O - collapses in VS\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER\
GAMEPLAYATTRIBUTE_VALUE_GETTER/SETTER/INITTER\

Console -> **showdebug abilitysystem**\
PgDown/PgUp\

## lesson 27. Effect Actor
UAbilitySystemComponent::GetSet<T>\
UAbilitySystemComponent::GetAttributeSet\

<br><br>

# 5. Game UI

## lesson 28. Game UI Architecture
View (Widgets) -> Widget [Data] Controller -> Data Model\
*Note*: widget controller not controll widgets, so better name would be with Data word\

## lesson 30. 
Event Graph - *Collapse to Function*\
Variable - Category\

## lesson 32. 
APlayerController::GetHUD\

## lesson 33. 
UPROPERTY(*BlueprintAssignable*) - multicast Delegates only. Property should be exposed for assigning in blueprints.\

UCLASS(*BlueprintType*) - can be used for variables in blueprints\
UCLASS(*Blueprintable*) - acceptable for creating blueprints\

## lesson 34. Listining to attributes changes
UAbilitySystemComponent::GetGameplayAttributeValueChangeDelegate\
FOnAttributeChangeData\

<br><br>

# 6. Gameplay Effects

## lesson 36. Gameplay Effects
Data only\
Don't subclass UGameplayEffect (use instead Execution or MMC)\
Gameplay Effect Spec\

*Affect Attributes* through *Modifiers* and *Executions*\
*Modifiers* -> Modifier Op (Add, Multiply, Divide, Override) + Magnitude\
Magnitude Calculation Type (Scalable Float, Attribute Based, Custom (Modifier Magnitude Calculation MMC), Set by Caller(by Name/Tag))\
*Execution* -> Gameplay Effect Execution Calculation\

*Duration Policy* - Instant, Has Duration, Infinite
*Stacking*
*Add Gameplay Tags*
*Grant Abilities*


