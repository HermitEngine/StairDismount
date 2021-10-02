// Created 2021-10-1 by eugene@e-goh.com

#include "GameHUD.h"
#include "Engine/Canvas.h" 
#include "StairDismountGameModeBase.h"

constexpr int SPACING = 20;

//=============================================================================
void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }

    AStairDismountGameModeBase* GameMode = static_cast<AStairDismountGameModeBase*>(GetWorld()->GetAuthGameMode());
    DrawText(TEXT("Score: ") + FString::FromInt(GameMode->Score), FColor::Black, SPACING, SPACING, ScoreFont);
    DrawText(TEXT("Balls: ") + FString::FromInt(GameMode->Bullets), FColor::Black, SPACING, ScoreFont->GetMaxCharHeight() + SPACING, ScoreFont);
    DrawText(TEXT("Fire: Left Mouse\nForward: W\nBack: S\nLeft: A\nRight: D\nRestart: R"), 
        FColor::Black, SPACING, SPACING + ScoreFont->GetMaxCharHeight() * 3, SmallFont);
}