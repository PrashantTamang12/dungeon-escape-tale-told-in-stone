// Fill out your copyright notice in the Description page of Project Settings.
#include "Mover.h"
#include "Math/UnrealMathUtility.h"

UMover::UMover()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetOwner()->GetActorLocation();
    SetShouldMove(false);
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector CurrentLocation = GetOwner()->GetActorLocation();
    ReachedTarget = CurrentLocation.Equals(TargetLocation);

    if (!ReachedTarget)
    {
        float Speed = MoveOffset.Length() / MoveTime;
        FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
        GetOwner()->SetActorLocation(NewLocation);
    }
}

bool UMover::GetShouldMove()
{
    return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
    ShouldMove = NewShouldMove;

    if (ShouldMove)
    {
        TargetLocation = StartLocation + MoveOffset;
    }
    else
    {
        TargetLocation = StartLocation;
    }

    // ✅ Broadcast so Blueprints can play movement sounds
    OnMovementStateChanged.Broadcast(ShouldMove);
}