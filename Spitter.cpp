// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "FP_MainCCharacter.h"
#include "SpitterProjectile.h"
#include "Spitter.h"

// Sets default values
ASpitter::ASpitter() //Spitter Constructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SpawnBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawn"));
    SpawnBullet->SetupAttachment(RootComponent);
	SpawnBullet->SetRelativeLocation(FVector(200.0f, 0.0f,0.0f));
	
	SpawnBullet2 = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawn2"));
	SpawnBullet2->SetupAttachment(Body);
	SpawnBullet2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRefer(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (MeshRefer.Succeeded()) { Body->SetStaticMesh(MeshRefer.Object); }

	Body->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	Body->SetupAttachment(RootComponent);

	FHealth = 4.0f;
	FDamage = 2.0f;

	BHasShot = false;

	
}

// Called when the game starts or when spawned
void ASpitter::BeginPlay()
{
	Super::BeginPlay();
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ASpitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FCurrentLocation = GetActorLocation();

	FPlayerLocation = FP_MainCCharacter->GetActorLocation();

	PlayerActorDistance = sqrt(FMath::Square(FPlayerLocation[0] - FCurrentLocation[0]) + FMath::Square(FPlayerLocation[1] - FCurrentLocation[1]) + FMath::Square(FPlayerLocation[2] - FCurrentLocation[2]));
}

// Called to bind functionality to input
void ASpitter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpitter::CaveResetSpitter()  //Function Called when player dies to reset all enemies
{
	Destroy();
}

void ASpitter::SpitterGetHit(float WolfReceivedDamage)  //Function Calles when Spitter gets hit
{
	FHealth = FHealth - WolfReceivedDamage;

	if (FHealth <= 0)
	{
		FP_MainCCharacter->MonsterKilled();
		Destroy();
	}

}

void ASpitter::ResetSpitTimer()  //Timer for Range Attack
{
	BHasShot = false;
}

void ASpitter::ShootSpitter() //Shoot Range Attack
{
	BHasShot = true;



	

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		
		const FRotator SpawnRotation = GetActorRotation();

		
		FVector SpawnLocation = SpawnBullet->GetComponentLocation();



		World->SpawnActor<AActor>(SpitterProjectileBP,SpawnLocation, SpawnRotation);
		
	}
	
}

