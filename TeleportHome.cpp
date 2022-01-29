// Fill out your copyright notice in the Description page of Project Settings.
#include "TeleportHome.h"
#include "Components/BoxComponent.h"
#include "FP_MainCCharacter.h"


// Sets default values
ATeleportHome::ATeleportHome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleportHome::OnOverlapBegin);
	HomeFromGolem = CreateDefaultSubobject<UBoxComponent>(TEXT("GolemHome"));
	HomeFromGolem->OnComponentBeginOverlap.AddDynamic(this, &ATeleportHome::OnOverlapBegin);

	HomeFromMine1 = CreateDefaultSubobject<UBoxComponent>(TEXT("HomeFromMine1"));
	HomeFromMine1->OnComponentBeginOverlap.AddDynamic(this, &ATeleportHome::OnOverlapBegin);

	TeleportHomeCave2 = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportHomeCave2"));
	TeleportHomeCave2->OnComponentBeginOverlap.AddDynamic(this, &ATeleportHome::OnOverlapBegin);

	PlayerTeleportComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent"));
}


// Called when the game starts or when spawned
void ATeleportHome::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportHome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ATeleportHome::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FP_MainCCharacter->BInCaveFight == false) {

		FP_MainCCharacter->SetActorLocation(PlayerTeleportComponent->GetComponentLocation()); //Testing
		FP_MainCCharacter->BInCaveFight = false;
		FP_MainCCharacter->FP_Health = FP_MainCCharacter->FP_MaxHealth;
		FP_MainCCharacter->BAtSurface = true;
	}
}

























