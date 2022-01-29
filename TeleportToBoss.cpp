// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainCCharacter.h"

#include"CaveManage.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"
#include "TeleportToBoss.h"

// Sets default values
ATeleportToBoss::ATeleportToBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Boss1 = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportToBoss1"));
	Boss1->OnComponentBeginOverlap.AddDynamic(this, &ATeleportToBoss::OnOverlapBegin);

	TeleportToBoss1 = CreateDefaultSubobject<USceneComponent>(TEXT("BossTeleportComponent"));


}



// Called when the game starts or when spawned
void ATeleportToBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportToBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportToBoss::TeleportToBoss()
{
	FP_MainCCharacter->SetActorLocationAndRotation(TeleportToBoss1->GetComponentLocation(), TeleportToBoss1->GetComponentRotation());

	FP_MainCCharacter->GetController()->SetControlRotation(TeleportToBoss1->GetComponentRotation());
}

void ATeleportToBoss::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FP_MainCCharacter->BossKey1 >= 1) {
		FP_MainCCharacter->BossKey1--;
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
		if (OtherActor == FP_MainCCharacter)
		{
			TeleportToBoss(); 
			FP_MainCCharacter->BInCaveFight = true;
			CaveManage->GolemCaveManage();

		}
	}
}