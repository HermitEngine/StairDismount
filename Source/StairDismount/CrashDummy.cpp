// Fill out your copyright notice in the Description page of Project Settings.


#include "CrashDummy.h"
#include "StairDismountGameModeBase.h"

//=============================================================================
ACrashDummy::ACrashDummy()
{
	PrimaryActorTick.bCanEverTick = true;
}

//=============================================================================
void ACrashDummy::BeginPlay()
{
	Super::BeginPlay();
}

//=============================================================================
void ACrashDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//=============================================================================
void ACrashDummy::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	float delta = (MyComp->GetComponentVelocity() - Other->GetVelocity()).Size();
	if (delta > 5.f)
	{
		AStairDismountGameModeBase* GameMode = static_cast<AStairDismountGameModeBase*>(GetWorld()->GetAuthGameMode());
		GameMode->Score += delta;
	}
}



