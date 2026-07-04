// Fill out your copyright notice in the Description page of Project Settings.
#include "TriggerComponent.h" // ⚠️ THIS MUST BE THE VERY FIRST LINE OF CODE
#include "Dungeon.h"          // Module header comes second

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    // Find Mover component on assigned actor
    if (MoverActor)
    {
        Mover = MoverActor->FindComponentByClass<UMover>();
        if (!Mover) UE_LOG(LogTemp, Warning, TEXT("Failed to find Mover on %s"), *MoverActor->GetName());
    }

    // Find Rotator component on assigned actor
    if (RotatorActor)
    {
        Rotator = RotatorActor->FindComponentByClass<URotator_>();
        if (!Rotator) UE_LOG(LogTemp, Warning, TEXT("Failed to find Rotator on %s"), *RotatorActor->GetName());
    }

    // Only bind overlap events for pressure plates
    if (isPressurePlate)
    {
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
    }
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("Pressure Plate Activator"))
    {
        ActivatorCount++;
        if (!isTriggered) Trigger(true);
    }
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->ActorHasTag("Pressure Plate Activator"))
    {
        ActivatorCount--;
        if (isTriggered && ActivatorCount == 0) Trigger(false);
    }
}

// ✅ Single definition passing bForceSound to Rotator only
void UTriggerComponent::Trigger(bool NewTriggerValue, bool bForceSound)
{
    isTriggered = NewTriggerValue;

    // Mover doesn't need force-sound logic
    if (Mover) Mover->SetShouldMove(isTriggered);

    // Rotator receives force-sound flag for Lock interactions
    if (Rotator) Rotator->SetShouldRotate(isTriggered, bForceSound);

    // Broadcast for Blueprint lock sounds/animations
    OnLockStateChanged.Broadcast(isTriggered);

    if (!Mover && !Rotator)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has neither Mover nor Rotator to trigger"), *GetOwner()->GetName());
    }
}