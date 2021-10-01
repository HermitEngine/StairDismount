// Created 2021-10-1 by eugene@e-goh.com

#include "StairDismountGameModeBase.h"

//=============================================================================
void AStairDismountGameModeBase::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Welcome To StairDismount"));
}