// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "FP_MainCCharacter.h"
#include "TeleportToMine.h"

// Sets default values
ATeleportToMine::ATeleportToMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleportToMine::OnOverlapBegin);
	

	PlayerTeleportComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent"));

}


// Called when the game starts or when spawned
void ATeleportToMine::BeginPlay()
{
	Super::BeginPlay();

	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void ATeleportToMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportToMine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (FP_MainCCharacter->BInCaveFight == false && FP_MainCCharacter->BossBeaten >=1)
	{


		FP_MainCCharacter->GetController()->SetControlRotation(PlayerTeleportComponent->GetComponentRotation());
	
		FP_MainCCharacter->SetActorLocation(PlayerTeleportComponent->GetComponentLocation()); //Testing
		FP_MainCCharacter->BInCaveFight = false;
		FP_MainCCharacter->FP_Health = FP_MainCCharacter->FP_MaxHealth;
	}
}
