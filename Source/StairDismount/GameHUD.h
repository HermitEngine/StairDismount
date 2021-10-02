// Created 2021-10-1 by eugene@e-goh.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

//=============================================================================
UCLASS() class STAIRDISMOUNT_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly) UTexture2D* CrosshairTexture;
	UPROPERTY(EditDefaultsOnly) UFont* ScoreFont;
	UPROPERTY(EditDefaultsOnly) UFont* SmallFont;
};
