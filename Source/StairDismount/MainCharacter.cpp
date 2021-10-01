// Created 2021-10-1 by eugene@e-goh.com

#include "MainCharacter.h"

//=============================================================================
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

//=============================================================================
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Main Character initialized and ready to go"));
}

//=============================================================================
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//=============================================================================
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Yaw", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Pitch", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::Shoot);
}

//=============================================================================
void AMainCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

//=============================================================================
void AMainCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

//=============================================================================
void AMainCharacter::Shoot()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			ABullet* Projectile = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, CameraRotation, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = CameraRotation.Vector();
				Projectile->ShootInDirection(LaunchDirection);
			}
		}
	}
}