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
Don't subclass UGameplayEffect, only Blueprints (use instead Execution or MMC)\
Gameplay Effect Spec\

*Affect Attributes* through *Modifiers* and *Executions*\
*Modifiers* -> Modifier Op (Add, Multiply, Divide, Override) + Magnitude + Tags\
Magnitude Calculation Type (Scalable Float, Attribute Based (lesson.66), Custom (Modifier Magnitude Calculation MMC), Set by Caller(by Name/Tag))\
*Execution* -> Gameplay Effect Execution Calculation\

*Duration Policy* - Instant, Has Duration, Infinite\
*Stacking*\
*Add Gameplay Tags*\
*Grant Abilities*\

## lesson 37. Effect Actor Improved
UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent\
UAbilitySystemGlobals::GetAbilitySystemComponentFromActor\

UAbilitySystemComponent::MakeEffectContext -> handle with TSharedPtr\
UAbilitySystemComponent::MakeOutgoingSpec -> handle with TSharedPtr\
UAbilitySystemComponent::ApplyGameplayEffect[Spec]To[Self/Target] - Spec used already created spec, without Spec will create locally inside\
return FActiveGameplayEffectHandle with int32 index\

*FGameplayEffectContext* - stores an instigator and related data, such as positions and targets. Great place to track transient information about an execution\

*FGameplayEffectSpec* (What UGameplayEffect (const data), Level, *Context*)\
Any state added to FGameplayEffectSpec must be handled in the move/copy constructor/operator!\
*FGameplayEffectSpecHandle* - generate a GameplayEffectSpec once and then reference it by handle, to apply it multiple times/multiple targets.\

## lesson 40. Duration Policy
*EGameplayEffectDurationType*\
Instant - permanent change to FGameplayAttributeData::BaseValue (which only includes permanent changes)\
HasDuration/Infinite - change FGameplayAttributeData::CurrentValue (which includes temporary buffs). Undone when effect removed.\
Can be periodic. Period tick will be permanent and not be undone at effect removed.\

## lesson 41. Effect Stacking
Without stacking effect just apply N times.\

*EGameplayEffectStackingType*\
AggregateBySource - each caster has its own stack (instigator/owner of component)\
AggregateByTarget - each target has its own stack\

## lesson 45. Attribute Change Clamp
good for clamps\
UAttributeSet::PreAttributeBaseChange\
UAttributeSet::PreAttributeChange (more info in 63 lesson)\ 

## lesson 46.
UAttributeSet::PostGameplayEffectExecute\
FGameplayEffectModCallbackData (containt EffectSpec, ModifierEvaluatedData, Target ASC)\
*FGameplayModifierEvaluatedData* - Data that describes what happened in an attribute modification\
UAbilitySystemComponent::*AbilityActorInfo* - Cached off data about the owning actor\
FGameplayEffectContextHandle::Get[Original]InstigatorAbilitySystemComponent\

TEnumAsByte - Template to store enumeration values as bytes in a type-safe way\

## lesson 47. Curve Tables for Scalable Floats

<br><br>

# 7. Gameplay Tags

## lesson 48. Gameplay Tags
Gameplay Tag Manager -> Gameplay Tags\

Implement IGameplayTagAssetInterface (like UAbilitySystemComponent)\
GetOwnedGameplayTags = 0\
HasMatchingGameplayTag\
HasAllMatchingGameplayTags\
HasAnyMatchingGameplayTags\
FGameplayTagContainer -> FGameplayTag (GAS use FGameplayTagCountContainer)\

Gameplay Effects can give tags to ASC on apply and remove tags after (e.g silense tag which block ASC ability use)\
Also used for identify inputs,abilities, attributes, damage types, debuffs\

## lesson 49. Creating Gameplay Tags in the Editor
Project Settings - Gameplay Tags\
Config/DefaultGameplayTags.ini\
Config/Tags/*.ini\

## lesson 50. Creating Gameplay Tags from Data Tables
Miscellaneous - Data Table - GameplayTagTableRow\
Project Settings - Gameplay Tags - Gameplay Tag Table List\

## lesson 52. Apply Gameplay Tags with Effects
Tags can stack, but count only effect application (not effect stacking if enabled)\

Combined = (Inherited + Added) - Removed (if parent has)\
Asset Tags - current asset tags\
Target/Granted Tags - applied to target actor (*instant effect dont grant tags*) \

## lesson 53. Gameplay Effect Delegates
FOnGameplayEffectAppliedDelegate\

## lesson 54. Get Effect Tags
FGameplayEffectSpec::GetAllAssetTags\
FGameplayEffectSpec::GetAllGrantedTags\

## lesson 56. UI Widget Data Table
FTableRowBase\
UDataTable\

## lesson 57. Retrieving Rows from Data Tables
UDataTable::FindRow<T>\

## lesson 58. Broadcasting Data Table Rows
FGameplayTag::RequestGameplayTag\
FGameplayTag::MatchesTag\
Event Graph - Break (break structure to fields)\

## lesson 60. Animating the Message Widget
Widget Animation - Show the animation keys in curve editor - Add key\
Event Graph - Add Custom Event \ Delay [Next Tick]\

## lesson 62. Ghost Globe
UKismetMathLibrary::FInterpTo\
*Note*: if child bp created with disabled tick event in parent, then you enable it in parent, need to recreate this node at child\

## lesson 63. Properly Clamping Attributes
UAttributeSet::PreAttributeBaseChange - NewValue affects **only** BaseValue and call only for instanse and periodic cases\
UAttributeSet::PreAttributeChange - New Value affects **only** CurrentValue and call in all cases\

<br><br>

# 8. RPG Attributes

## lesson 64. Initialize Attributes from a Data Table
ASC property window - Default Starting Data\
Data Table - Attribute Meta Data (FAttributeMetaData) -> RowName [AttributeSetClassName].[AttributeName]\

## lesson 66. Attribute Based Modifiers
## lesson 67. Modifier Order of Operations
Clamping in PreAttribute[Base]Change called after **every** modifier applied\

## lesson 68. Attribute Based Modifier Coefficients
(Value + Pre Multiply Additive Value) * Coefficient + Post Multiply Additive Value\

## lesson 73. Modifier Magnitude Calculations
UGameplayModMagnitudeCalculation::CalculateBaseMagnitude_Implementation\
UGameplayModMagnitudeCalculation::RelevantAttributesToCapture\
FGameplayEffectAttributeCaptureDefinition::bSnapshot - when capture attribute, false at effect application / true at effect spec created\

UGameplayModMagnitudeCalculation::GetCapturedAttributeMagnitude\
FGameplayEffectSpec::CapturedSourceTags/CapturedTargetTags (FTagContainerAggregator)\
FAggregatorEvaluateParameters\
*Note* - MMC looks better in blueprints (select attribute to capture, factors, etc)\

<br><br>

# 9. Attribute Menu

## lesson 77. Attribute Menu - Text Value Row
Named Slot - for acting as placeholders in templated UI\

## lesson 79. Attribute Menu - Construction
Wrap Box\

## lesson 83. Closing the Attribute Menu
Event Dispatches\

## lesson 85. Gameplay Tags Singleton
UGameplayTagsManager::AddNativeGameplayTag\

## lesson 86. Aura Asset Manager
UAssetManager - framework for managing Assets that can divide content into chunks.\
Provides a set of tools to help audit disk and memory usage\
DefaultEngine.ini - AssetManagerClassName=/Script/Aura.AuraAssetManager\

## lesson 88. Attribute Info Data Asset
UDataAsset - asset that stores data related to a particular system in an instance of its class\

## lesson 90. Aura Ability System Blueprint Library
UBlueprintFunctionLibrary\
BlueprintPure - not affect the owning object in any way and can be executed in a Blueprint or Level Blueprint graph.\
*Do not cache* their results, therefore should be cautious when doing any non-trivial amount of work\
UGameplayStatics::GetPlayerController\
*Note* - looks better to make singleton like WidgetsDataSystem where store all WidgetDataControllers\

## lesson 94. Mapping Tags to Attributes
DECLARE_DELEGATE_RetVal\