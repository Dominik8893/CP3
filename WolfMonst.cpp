// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainCCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "WolfMonst.h"

// Sets default values
AWolfMonst::AWolfMonst() //WolfMonster Constructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRefer(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (MeshRefer.Succeeded()) { Body->SetStaticMesh(MeshRefer.Object); }

	Body->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	Body->SetupAttachment(RootComponent);

	FHealth = 6.0f;
	FDamage = 2.0f;
}

// Called when the game starts or when spawned
void AWolfMonst::BeginPlay()
{
	Super::BeginPlay();
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Body->SetVisibility(false);
	
}

// Called every frame
void AWolfMonst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FCurrentLocation = GetActorLocation();

	FPlayerLocation = FP_MainCCharacter->GetActorLocation();
	
	PlayerActorDistance = sqrt(FMath::Square(FPlayerLocation[0] - FCurrentLocation[0]) + FMath::Square(FPlayerLocation[1] - FCurrentLocation[1]) + FMath::Square(FPlayerLocation[2] - FCurrentLocation[2]));
}

// Called to bind functionality to input
void AWolfMonst::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWolfMonst::CaveResetWolf()
{
	Destroy();
}

void AWolfMonst::WolfGetHit(float WolfReceivedDamage)
{
	FHealth = FHealth - WolfReceivedDamage;



	if (FHealth <= 0)
	{
		FP_MainCCharacter->MonsterKilled();
		Destroy();
	}
}



