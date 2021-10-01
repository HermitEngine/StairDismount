// Created 2021-10-1 by eugene@e-goh.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StairDismountGameModeBase.generated.h"

//=============================================================================
UCLASS() class STAIRDISMOUNT_API AStairDismountGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
	virtual void StartPlay() override;
};
