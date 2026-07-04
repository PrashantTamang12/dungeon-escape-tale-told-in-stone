// Fill out your copyright notice in the Description page of Project Settings.
#include "Rotator_.h" // ⚠️ CRITICAL: Must be first include
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

URotator_::URotator_()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void URotator_::BeginPlay()
{
    Super::BeginPlay();
    if (AActor* Owner = GetOwner())
    {
        StartRotation = Owner->GetActorRotation();
        TargetRotation = StartRotation;
    }
    // Initialize without broadcasting sound at game start
    SetShouldRotate(false);
}

void URotator_::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Owner = GetOwner();
    if (!Owner || ReachedTarget) return;

    const FRotator Current = Owner->GetActorRotation();
    const float Tolerance = 0.01f;
    ReachedTarget = Current.Equals(TargetRotation, Tolerance);

    if (!ReachedTarget)
    {
        const float SafeTime = FMath::Max(RotateTime, KINDA_SMALL_NUMBER);
        const FVector OffsetVec(RotOffset.Pitch, RotOffset.Yaw, RotOffset.Roll);
        const float TotalDegrees = OffsetVec.IsNearlyZero() ? 0.0f : OffsetVec.Size();
        const float DegreesPerSecond = TotalDegrees / SafeTime;

        const FRotator NewRot = FMath::RInterpConstantTo(Current, TargetRotation, DeltaTime, DegreesPerSecond);
        Owner->SetActorRotation(NewRot);
    }
}

// ✅ Single definition matching header signature exactly
void URotator_::SetShouldRotate(bool NewShouldRotate, bool bForceSound)
{
    bool WasMoving = !ReachedTarget;
    ShouldRotate = NewShouldRotate;

    // Always update target immediately for responsive reversal
    if (ShouldRotate)
    {
        TargetRotation = StartRotation + RotOffset;
    }
    else
    {
        TargetRotation = StartRotation;
    }

    ReachedTarget = false;

    // Only broadcast if door was at rest OR if forced by Lock interaction
    if (!WasMoving || bForceSound)
    {
        OnRotationStateChanged.Broadcast(ShouldRotate);
    }
}