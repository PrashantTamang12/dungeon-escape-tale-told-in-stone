// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DungeonCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

/**
 * A basic first person character
 */
UCLASS()
class DUNGEON_API ADungeonCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Pawn mesh: first person view (arms; seen only by self) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* FirstPersonMesh;

    /** First person camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FirstPersonCameraComponent;

protected:
    /** Jump Input Action */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LookAction;

    /** Mouse Look Input Action */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseLookAction;

    /** Interact Input Action (E key - for items/locks) */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InteractAction;

    /** Door Interaction Input Action (F key - for InteractableDoor only) */
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* DoorInteractAction;

public:
    ADungeonCharacter();

    FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCameraComponent; }

    // Called every frame to update the interaction prompt
    virtual void Tick(float DeltaTime) override;

    // UI Events (Implemented in Blueprint, do not implement in C++)
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnInteractableFound(const FString& PromptText);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnInteractableLost();

    /** Returns the first person mesh */
    USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

    /** Returns first person camera component */
    UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

    /** E Key: Handles Items and Locks ONLY */
    void Interact();

    /** F Key: Handles BP_CellDoor_Auto (InteractableDoor) ONLY */
    void InteractWithDoor();

    UPROPERTY(EditAnywhere)
    float MaxInteractionDistance = 300.0f;

    UPROPERTY(EditAnywhere)
    float InteractionSphereRadius = 10.0f;

protected:
    /** Called from Input Actions for movement input */
    void MoveInput(const FInputActionValue& Value);

    /** Called from Input Actions for looking input */
    void LookInput(const FInputActionValue& Value);

    /** Handles aim inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoAim(float Yaw, float Pitch);

    /** Handles move inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoMove(float Right, float Forward);

    /** Handles jump start inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpStart();

    /** Handles jump end inputs from either controls or UI interfaces */
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpEnd();

    /** Set up input action bindings */
    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
    // Inventory
    UPROPERTY(VisibleAnywhere)
    TArray<FString> ItemList;

    // Interaction System Helpers
    bool DoInteractionSweep(FHitResult& OutHitResult);
    void UpdateInteractionPrompt();

    UPROPERTY()
    AActor* CurrentHoveredActor = nullptr;
};