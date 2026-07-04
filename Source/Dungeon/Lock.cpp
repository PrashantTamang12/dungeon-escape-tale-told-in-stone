// Fill out your copyright notice in the Description page of Project Settings.
#include "Lock.h"

ALock::ALock()
{
    PrimaryActorTick.bCanEverTick = true;
    Tags.Add("Lock");

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
    SetRootComponent(RootComp);

    TriggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Comp"));
    TriggerComp->SetupAttachment(RootComp);

    KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Item Mesh"));
    KeyItemMesh->SetupAttachment(RootComp);
}

void ALock::BeginPlay()
{
    Super::BeginPlay();

    if (TriggerComp)
    {
        TriggerComp->OnLockStateChanged.AddDynamic(this, &ALock::HandleTriggerLockStateChanged);
    }

    SetIsKeyPlaced(false);
}

void ALock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALock::SetIsKeyPlaced(bool NewIsKeyPlaced)
{
    IsKeyPlaced = NewIsKeyPlaced;

    if (TriggerComp)
    {
        // ✅ Force sound on lock interaction regardless of door state
        TriggerComp->Trigger(NewIsKeyPlaced, true);
    }

    KeyItemMesh->SetVisibility(NewIsKeyPlaced);
}

bool ALock::GetIsKeyPlaced()
{
    return IsKeyPlaced;
}

void ALock::HandleTriggerLockStateChanged(bool bIsLocked)
{
    OnLockStateChanged(bIsLocked);
}