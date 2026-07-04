// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerComponent.h"
#include "Lock.generated.h"

UCLASS()
class DUNGEON_API ALock : public AActor
{
    GENERATED_BODY()

public:
    ALock();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Lock")
    void SetIsKeyPlaced(bool NewIsKeyPlaced);

    // ✅ Matches .cpp exactly (no const mismatch)
    UFUNCTION(BlueprintPure, Category = "Lock")
    bool GetIsKeyPlaced();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* RootComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTriggerComponent* TriggerComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* KeyItemMesh;

    UFUNCTION(BlueprintImplementableEvent, Category = "Lock")
    void OnLockStateChanged(bool bIsLocked);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock|Config")
    FName KeyItemName;

private:
    UFUNCTION()
    void HandleTriggerLockStateChanged(bool bIsLocked);

    UPROPERTY(VisibleAnywhere, Category = "Lock|State")
    bool IsKeyPlaced = false;
};