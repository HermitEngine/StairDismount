// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "CrashDummy.generated.h"

//=============================================================================
UCLASS() class STAIRDISMOUNT_API ACrashDummy : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	ACrashDummy();
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
protected:
	virtual void BeginPlay() override;
};
