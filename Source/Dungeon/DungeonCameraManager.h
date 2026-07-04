// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "DungeonCameraManager.generated.h"

/**
 * ADungeonCameraManager: Custom camera manager for first-person dungeon gameplay.
 * Limits vertical look angle to prevent unrealistic camera rotation.
 */
UCLASS()
class DUNGEON_API ADungeonCameraManager : public APlayerCameraManager
{
    GENERATED_BODY()

public:
    /** Constructor - sets default view pitch limits */
    ADungeonCameraManager();
};