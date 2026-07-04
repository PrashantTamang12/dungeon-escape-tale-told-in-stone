// Fill out your copyright notice in the Description page of Project Settings.
#include "CollectItem.h"

ACollectItem::ACollectItem()
{
    PrimaryActorTick.bCanEverTick = true;

    // Tag used by DungeonCharacter to identify this as a collectible
    Tags.Add("Collectable Item");
}

void ACollectItem::BeginPlay()
{
    Super::BeginPlay();
}

void ACollectItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACollectItem::SetIsCollected(bool bNewIsCollected)
{
    // Prevent redundant state changes and duplicate events
    if (bIsCollected == bNewIsCollected) return;

    // Update internal state first
    bIsCollected = bNewIsCollected;

    // CRITICAL: Fire Blueprint event FIRST while actor is still visible/active
    // This ensures sounds play correctly before the actor is hidden
    OnCollectibleStateChanged(bIsCollected);

    // THEN hide/disable the actor to prevent interaction while collected
    SetActorHiddenInGame(bIsCollected);
    SetActorEnableCollision(!bIsCollected);
}