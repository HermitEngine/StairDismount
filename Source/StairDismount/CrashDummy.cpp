// Fill out your copyright notice in the Description page of Project Settings.


#include "CrashDummy.h"

//=============================================================================
ACrashDummy::ACrashDummy()
{
	PrimaryActorTick.bCanEverTick = true;
}

//=============================================================================
void ACrashDummy::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Crash Dummy initialized and ready to go"));
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

	float delta = (GetVelocity() - Other->GetVelocity()).Size();
	if (delta > 5.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(delta));
	}
}



