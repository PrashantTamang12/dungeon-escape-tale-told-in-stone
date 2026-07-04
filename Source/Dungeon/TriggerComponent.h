// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Rotator_.h"

#include "TriggerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockStateChangedSignature, bool, bIsLocked);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_API UTriggerComponent : public UBoxComponent
{
    GENERATED_BODY()

public:
    UTriggerComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Blueprint-assignable delegate for lock state changes
    UPROPERTY(BlueprintAssignable, Category = "Trigger")
    FOnLockStateChangedSignature OnLockStateChanged;

    // Mover Setup
    UPROPERTY(EditAnywhere)
    AActor* MoverActor;

    UPROPERTY(VisibleAnywhere)
    UMover* Mover;

    // Rotator Setup
    UPROPERTY(EditAnywhere)
    AActor* RotatorActor;

    UPROPERTY(VisibleAnywhere)
    URotator_* Rotator;

    // Overlap Handlers
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY(EditAnywhere)
    bool isPressurePlate = false;

    UPROPERTY(VisibleAnywhere)
    bool isTriggered = false;

    // ✅ Single declaration with bForceSound parameter
    void Trigger(bool NewTriggerValue, bool bForceSound = false);

    UPROPERTY(VisibleAnywhere)
    int32 ActivatorCount = 0;
};