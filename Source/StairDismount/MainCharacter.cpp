// Created 2021-10-1 by eugene@e-goh.com

#include "MainCharacter.h"
#include "StairDismountGameModeBase.h"
#include "Kismet/GameplayStatics.h"

//=============================================================================
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

//=============================================================================
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySound2D(this, StartSound);
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
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMainCharacter::Reload);
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
		AStairDismountGameModeBase* GameMode = static_cast<AStairDismountGameModeBase*>(GetWorld()->GetAuthGameMode());
		if (World && GameMode->Bullets > 0)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			ABullet* Projectile = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, CameraRotation, SpawnParams);

			if (Projectile)
			{
				GameMode->Bullets -= 1;
				FVector LaunchDirection = CameraRotation.Vector();
				Projectile->ShootInDirection(LaunchDirection);
				UGameplayStatics::PlaySoundAtLocation(this, WhooshSound, MuzzleLocation);
			}
		}
	}
}

//=============================================================================
void AMainCharacter::Reload()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}