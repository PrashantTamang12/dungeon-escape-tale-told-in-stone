// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rotator_.generated.h"

// ✅ Delegate MUST be declared before the class for UHT parsing
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationStateChangedSignature, bool, bIsRotating);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_API URotator_ : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere)
    bool ShouldRotate = false;

public:
    URotator_();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Rotation State Variables
    FRotator StartRotation;
    FRotator TargetRotation;

    UPROPERTY(EditAnywhere)
    FRotator RotOffset;

    UPROPERTY(EditAnywhere)
    float RotateTime = 4.0f;

    UPROPERTY(VisibleAnywhere)
    bool ReachedTarget = false;

    bool GetShouldRotate() const { return ShouldRotate; }

    // ✅ Single declaration with default parameter for Lock force-sound override
    void SetShouldRotate(bool NewShouldRotate, bool bForceSound = false);

    // ✅ Blueprint-Assignable Delegate Property
    UPROPERTY(BlueprintAssignable, Category = "Rotator")
    FOnRotationStateChangedSignature OnRotationStateChanged;
};