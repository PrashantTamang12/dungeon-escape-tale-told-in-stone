// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

// ✅ Delegate declaration for movement state changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementStateChangedSignature, bool, bIsMoving);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_API UMover : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere)
    bool ShouldMove = false;

public:
    UMover();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    FVector StartLocation;
    FVector TargetLocation;

    UPROPERTY(EditAnywhere)
    FVector MoveOffset;

    UPROPERTY(EditAnywhere)
    float MoveTime = 4.0f;

    UPROPERTY(VisibleAnywhere)
    bool ReachedTarget = false;

    bool GetShouldMove();
    void SetShouldMove(bool NewShouldMove);

    // ✅ Blueprint-Assignable Delegate Property
    UPROPERTY(BlueprintAssignable, Category = "Mover")
    FOnMovementStateChangedSignature OnMovementStateChanged;
};