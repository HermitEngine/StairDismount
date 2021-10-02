// Created 2021-10-1 by eugene@e-goh.com

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bullet.generated.h"

//=============================================================================
UCLASS() class STAIRDISMOUNT_API ABullet : public APawn
{
	GENERATED_BODY()

public:
	ABullet();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ShootInDirection(const FVector& ShootDirection);

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement) UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) UStaticMeshComponent* ProjectileMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Movement) UMaterialInstanceDynamic* ProjectileMaterialInstance;
	UPROPERTY(EditDefaultsOnly) USoundBase* PingSound;

protected:
	virtual void BeginPlay() override;
};
