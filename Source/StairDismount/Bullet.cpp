// Created 2021-10-1 by eugene@e-goh.com

#include "Bullet.h"
#include "Animation/SkeletalMeshActor.h"

//=============================================================================
ABullet::ABullet()
{
 	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 2000.0f;
		ProjectileMovementComponent->MaxSpeed = 2000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.2f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	if (!PingSound)
	{
		static ConstructorHelpers::FObjectFinder<USoundBase>SoundWave(TEXT("SoundWave'/Game/Sounds/ping.ping'"));
		if (SoundWave.Succeeded())
		{
			PingSound = SoundWave.Object;
		}
	}

	InitialLifeSpan = 3.0f;
}

//=============================================================================
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

//=============================================================================
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//=============================================================================
void ABullet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//=============================================================================
void ABullet::ShootInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//=============================================================================
void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherActor->IsA<ASkeletalMeshActor>())
	{
		ASkeletalMeshActor* CrashDummy = static_cast<ASkeletalMeshActor*>(OtherActor);
		CrashDummy->GetSkeletalMeshComponent()->SetSimulatePhysics(true);
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 10.0f, Hit.ImpactPoint);
		UGameplayStatics::PlaySoundAtLocation(this, PingSound, Hit.ImpactPoint);
	}

	Destroy();
}