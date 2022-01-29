// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "FP_MainCCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RockProjectile.h"

FTimerHandle CanHitTimer;
// Sets default values
ARockProjectile::ARockProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BCanHit = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ARockProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2100.f;
	ProjectileMovement->MaxSpeed = 2400.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingAccelerationMagnitude = 40000.f;

	ProjectileMovement->ProjectileGravityScale = 2.2;
	// Die after 3 seconds by default
	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void ARockProjectile::BeginPlay()
{
	Super::BeginPlay();

	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(CanHitTimer, this, &ARockProjectile::CanHitF, 0.5f, false, 0.5f);//Setting Timer
	
	ProjectileMovement->HomingTargetComponent = FP_MainCCharacter->GetRootComponent();
}

// Called every frame
void ARockProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARockProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == FP_MainCCharacter)
	{
		FP_MainCCharacter->ReceiveDamage(3.0f); 
	}
	
	if (BCanHit == true)
	{
		Destroy();
	}
	
}

void ARockProjectile::CanHitF()
{
	BCanHit = true;
	SetActorEnableCollision(true);
}

