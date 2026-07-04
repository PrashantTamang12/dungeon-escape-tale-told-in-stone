// Copyright Epic Games, Inc. All Rights Reserved.
#include "DungeonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CollectItem.h"
#include "Lock.h"
#include "Rotator_.h"
#include "Dungeon.h" // ✅ RESTORED: Required for LogDungeon category

ADungeonCharacter::ADungeonCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
    FirstPersonMesh->SetupAttachment(GetCapsuleComponent());
    FirstPersonMesh->SetOnlyOwnerSee(true);
    FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
    FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 64.0f), FRotator::ZeroRotator);
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
    FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
    FirstPersonCameraComponent->bEnableFirstPersonScale = true;
    FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
    FirstPersonCameraComponent->FirstPersonScale = 0.6f;

    GetMesh()->SetOwnerNoSee(true);
    GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
    GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
    GetCharacterMovement()->AirControl = 0.5f;
}

void ADungeonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADungeonCharacter::DoJumpStart);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADungeonCharacter::DoJumpEnd);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::MoveInput);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::LookInput);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADungeonCharacter::LookInput);

        // ✅ E Key: ONLY for Items and Locks
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADungeonCharacter::Interact);

        // ✅ F Key: ONLY for BP_CellDoor_Auto (tagged "InteractableDoor")
        EnhancedInputComponent->BindAction(DoorInteractAction, ETriggerEvent::Started, this, &ADungeonCharacter::InteractWithDoor);
    }
    else
    {
        UE_LOG(LogDungeon, Error, TEXT("'%s' Failed to find an Enhanced Input Component!"), *GetNameSafe(this));
    }
}

bool ADungeonCharacter::DoInteractionSweep(FHitResult& OutHitResult)
{
    if (!FirstPersonCameraComponent)
    {
        UE_LOG(LogDungeon, Error, TEXT("DoInteractionSweep: FirstPersonCameraComponent is null"));
        return false;
    }

    FVector Start = FirstPersonCameraComponent->GetComponentLocation();
    FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * MaxInteractionDistance);
    FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractionSphereRadius);

    // Ignore self so trace doesn't hit player capsule
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    // ✅ Uses ECC_GameTraceChannel2 as required
    return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere, QueryParams);
}

void ADungeonCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateInteractionPrompt();
}

void ADungeonCharacter::UpdateInteractionPrompt()
{
    FHitResult HitResult;
    AActor* HitActor = DoInteractionSweep(HitResult) ? HitResult.GetActor() : nullptr;

    if (HitActor == CurrentHoveredActor) return;
    CurrentHoveredActor = HitActor;

    if (!HitActor)
    {
        OnInteractableLost();
        return;
    }

    // ✅ E Key Prompts
    if (HitActor->ActorHasTag("Collectable Item"))
    {
        OnInteractableFound(TEXT("[E] Pick Up"));
    }
    else if (HitActor->ActorHasTag("Lock"))
    {
        ALock* LockActor = Cast<ALock>(HitActor);
        if (!LockActor) return;

        if (!LockActor->GetIsKeyPlaced())
        {
            OnInteractableFound(
                ItemList.Contains(LockActor->KeyItemName.ToString())
                ? TEXT("[E] Place Key")
                : TEXT("You need a key..."));
        }
        else
        {
            OnInteractableFound(TEXT("[E] Take Key"));
        }
    }
    // ✅ F Key Prompt - Matches BP_CellDoor_Auto tag exactly
    // BP_CellDoor_Rotate has NO tag, so it is safely ignored here
    else if (HitActor->ActorHasTag("InteractableDoor"))
    {
        URotator_* DoorRotator = HitActor->FindComponentByClass<URotator_>();
        if (DoorRotator)
        {
            FString Prompt = DoorRotator->GetShouldRotate() ? TEXT("[F] Close") : TEXT("[F] Open");
            OnInteractableFound(Prompt);
        }
        else
        {
            OnInteractableLost();
        }
    }
    else
    {
        OnInteractableLost();
    }
}

void ADungeonCharacter::Interact()
{
    FHitResult HitResult;
    if (!DoInteractionSweep(HitResult))
    {
        UE_LOG(LogDungeon, Display, TEXT("Shape Trace Hit Nothing"));
        return;
    }

    AActor* HitActor = HitResult.GetActor();
    if (!HitActor) return;

    // ✅ E Key Logic: ONLY Items and Locks. No door logic here.
    if (HitActor->ActorHasTag("Collectable Item"))
    {
        ACollectItem* CollectableItem = Cast<ACollectItem>(HitActor);
        if (CollectableItem)
        {
            if (!CollectableItem->GetIsCollected())
            {
                ItemList.Add(CollectableItem->ItemName.ToString());
                CollectableItem->SetIsCollected(true);
            }
            else
            {
                ItemList.RemoveSingle(CollectableItem->ItemName.ToString());
                CollectableItem->SetIsCollected(false);
            }
            OnInteractableLost();
            CurrentHoveredActor = nullptr;
        }
    }
    else if (HitActor->ActorHasTag("Lock"))
    {
        ALock* LockActor = Cast<ALock>(HitActor);
        if (LockActor)
        {
            if (!LockActor->GetIsKeyPlaced())
            {
                int32 ItemRemoved = ItemList.RemoveSingle(LockActor->KeyItemName.ToString());
                if (ItemRemoved)
                {
                    LockActor->SetIsKeyPlaced(true);
                }
                else
                {
                    UE_LOG(LogDungeon, Display, TEXT("!Key Item not in inventory!"));
                }
            }
            else
            {
                ItemList.Add(LockActor->KeyItemName.ToString());
                LockActor->SetIsKeyPlaced(false);
            }
            OnInteractableLost();
            CurrentHoveredActor = nullptr;
        }
    }
    // NOTE: Door logic is COMPLETELY REMOVED from Interact()
}

void ADungeonCharacter::InteractWithDoor()
{
    FHitResult HitResult;
    if (!DoInteractionSweep(HitResult)) return;

    AActor* HitActor = HitResult.GetActor();
    if (!HitActor) return;

    // ✅ F Key Logic: ONLY actors tagged "InteractableDoor"
    // BP_CellDoor_Rotate has NO tag, so pressing F near it does nothing
    if (HitActor->ActorHasTag("InteractableDoor"))
    {
        URotator_* DoorRotator = HitActor->FindComponentByClass<URotator_>();
        if (DoorRotator)
        {
            // Toggle rotation state. bForceSound=true ensures sound plays even if interrupted
            DoorRotator->SetShouldRotate(!DoorRotator->GetShouldRotate(), true);
        }
        OnInteractableLost();
        CurrentHoveredActor = nullptr;
    }
}

void ADungeonCharacter::MoveInput(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void ADungeonCharacter::LookInput(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void ADungeonCharacter::DoAim(float Yaw, float Pitch)
{
    if (GetController())
    {
        AddControllerYawInput(Yaw);
        AddControllerPitchInput(Pitch);
    }
}

void ADungeonCharacter::DoMove(float Right, float Forward)
{
    if (GetController())
    {
        AddMovementInput(GetActorRightVector(), Right);
        AddMovementInput(GetActorForwardVector(), Forward);
    }
}

void ADungeonCharacter::DoJumpStart() { Jump(); }
void ADungeonCharacter::DoJumpEnd() { StopJumping(); }