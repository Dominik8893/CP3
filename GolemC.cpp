// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "FP_MainCCharacter.h"
#include "Components/SphereComponent.h"
#include "RockProjectile.h"
#include "GolemC.h"



// Sets default values
AGolemC::AGolemC() //Constructor
{
	FHealth = 60.0f; // Setting the Health in the Constructor

	BHasShot = false;
	BIsOverlappingPlayer = false;
	IntMegaAttackReady = 0;

	RotatorMegaAttack = { 0.0f,0.0f,0.0f };;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	//Setting the meshes for our Golem
	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGolemC::OnOverlapBegin);
	MySphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGolemC::OnOverlapEnd);
    MySphereComponent->SetupAttachment(RootComponent);
	

	SpawnBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawn"));
	SpawnBullet->SetupAttachment(RootComponent);
	SpawnBullet->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));

	
	
}



// Called when the game starts or when spawned
void AGolemC::BeginPlay()
{
	Super::BeginPlay();

	
	MySphereComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
}

// Called every frame
void AGolemC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FCurrentLocation = GetActorLocation();

	FPlayerLocation = FP_MainCCharacter->GetActorLocation();

	PlayerActorDistance = sqrt(FMath::Square(FPlayerLocation[0] - FCurrentLocation[0]) + FMath::Square(FPlayerLocation[1] - FCurrentLocation[1]) + FMath::Square(FPlayerLocation[2] - FCurrentLocation[2]));
}

// Called to bind functionality to input
void AGolemC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGolemC::GolemGetHit(float FGolemHitDamage)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("HitGolem")));
	FHealth = FHealth - FGolemHitDamage;

	if (FHealth <= 0)
	{
		if (FP_MainCCharacter->BossBeaten < 1) { FP_MainCCharacter->BossBeaten = 1; }


		FP_MainCCharacter->MonsterKilled();
		Destroy();
	}



}

void AGolemC::GolemThrowStone() //Function for The Golem Throwing Stone Attack
{
	
	if (IntMegaAttackReady <3) { IntMegaAttackReady++; }


	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		const FRotator SpawnRotation = SpawnBullet->GetComponentRotation();


		FVector SpawnLocation = SpawnBullet->GetComponentLocation();
	

		if (RockProjectile != nullptr)
		{
			World->SpawnActor<AActor>(RockProjectile, SpawnLocation, SpawnRotation);
		}
	}
}
void AGolemC::GolemSlam()  //GolemSlam Attack when Player is Nearby
{
	if ( BIsOverlappingPlayer == true) { FP_MainCCharacter->ReceiveDamage(5); }
}

void AGolemC::GolemMegaAttack()  //MegaAttack Spawingn giant Rock after 3 Stone Throw Attacks
{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("GolemAttackMega")));

		IntMegaAttackReady = 0;

		UWorld* const World = GetWorld();

		if (World != nullptr)
		{

			

			FVector SpawnLocation = FP_MainCCharacter->GetActorLocation();

			SpawnLocation = { SpawnLocation[0],SpawnLocation[1] ,SpawnLocation[2]+ 1300 };
		
			if (MegaProjectile != nullptr)
			{
				World->SpawnActor<AActor>(MegaProjectile, SpawnLocation, RotatorMegaAttack);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("MegaProjectileMissing")));
			}
		}	
}


void AGolemC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)  //Event when Player starts overlapping
{
	
	if (OtherActor == FP_MainCCharacter)
	{
		BIsOverlappingPlayer = true;

	}
	
}

void AGolemC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)//Event when Player stops overlapping
{
	if (OtherActor == FP_MainCCharacter)
	{
		BIsOverlappingPlayer = false;
	}
	

}


