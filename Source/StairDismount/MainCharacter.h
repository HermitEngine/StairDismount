// Created 2021-10-1 by eugene@e-goh.com

#pragma once

#include "Bullet.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//=============================================================================
UCLASS() class STAIRDISMOUNT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void MoveForward(float Value);
	UFUNCTION() void MoveRight(float Value);
	UFUNCTION() void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class ABullet> ProjectileClass;

protected:
	virtual void BeginPlay() override;
};
