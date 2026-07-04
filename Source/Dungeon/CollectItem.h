// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectItem.generated.h"

/**
 * ACollectItem: Base class for pick-up-able items.
 * Supports toggle collection state and notifies Blueprints for sound/UI feedback.
 */
UCLASS()
class DUNGEON_API ACollectItem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACollectItem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // --- COLLECTION LOGIC ---

    /**
     * Toggles collection state. Plays sound BEFORE hiding actor.
     * @param bNewIsCollected True = collected/hidden, False = dropped/visible
     */
    UFUNCTION(BlueprintCallable, Category = "Collectible")
    void SetIsCollected(bool bNewIsCollected);

    /** Returns current collection state */
    UFUNCTION(BlueprintPure, Category = "Collectible")
    bool GetIsCollected() const { return bIsCollected; }

    // --- BLUEPRINT EVENTS ---

    /**
     * Called when item is picked up or dropped.
     * Implement in BP to play pickup/drop sounds.
     * @param bNewIsCollected New collection state
     */
    UFUNCTION(BlueprintImplementableEvent, Category = "Collectible")
    void OnCollectibleStateChanged(bool bNewIsCollected);

    // --- CONFIGURATION ---

    /** Unique identifier for this item (used in player inventory) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collectible|Config")
    FName ItemName;

private:
    /** Tracks whether item is currently collected */
    UPROPERTY(VisibleAnywhere, Category = "Collectible|State")
    bool bIsCollected = false;
};