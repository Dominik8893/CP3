// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"
#include "FP_MainCCharacter.h"
#include "CaveManage.h"
#include "Components/BoxComponent.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TestTeleport = -1;
	CaveNumber = 0;
	PreviousCaveNumber = 2;
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent2 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component2"));
	MyBoxComponent2->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent3 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component3"));
	MyBoxComponent3->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent4 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component4"));
	MyBoxComponent4->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent5 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component5"));
	MyBoxComponent5->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent6 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component6"));
	MyBoxComponent6->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	MyBoxComponent7 = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component7"));
	MyBoxComponent7->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);


	PlayerTeleportComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent"));
	PlayerTeleportComponent2 = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent1"));
	PlayerTeleportComponent3 = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent2"));
	PlayerTeleportComponent4 = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent3"));
	PlayerTeleportComponent5 = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent4"));
	PlayerTeleportComponent6 = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportComponent5"));

	/*
	Boss1 = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportToBoss1"));
	Boss1->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBeginBoss);

	TeleportToBoss1 = CreateDefaultSubobject<USceneComponent>(TEXT("BossTeleportComponent"));
	*/

}



// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	srand(time(NULL));
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::TeleportFromCave()
{        
	//Setting different caves after boss beaten


	switch (FP_MainCCharacter->BossBeaten)
	{
	case 0: {CaveNumber = rand() % 3; break; }
	case 1: {CaveNumber = rand() % 6; break; }
	}
		while (CaveNumber == PreviousCaveNumber)
		{
			CaveNumber = rand() % 3;
		}

		if (TestTeleport != -1) { CaveNumber = TestTeleport; }

		//CaveNumber = 3;
		
		if (CaveNumber == 0) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent->GetComponentLocation(), PlayerTeleportComponent->GetComponentRotation()); CaveManage->Cave1(); }
		if (CaveNumber == 1) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent2->GetComponentLocation(), PlayerTeleportComponent2->GetComponentRotation()); FP_MainCCharacter->GetController()->SetControlRotation(PlayerTeleportComponent2->GetComponentRotation()); CaveManage->Cave2();}
		if (CaveNumber == 2) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent3->GetComponentLocation(), PlayerTeleportComponent3->GetComponentRotation()); CaveManage->Cave3();}
		if (CaveNumber == 3) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent4->GetComponentLocation(), PlayerTeleportComponent4->GetComponentRotation()); FP_MainCCharacter->GetController()->SetControlRotation(PlayerTeleportComponent4->GetComponentRotation()); CaveManage->Cave4();}
		if (CaveNumber == 4) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent5->GetComponentLocation(), PlayerTeleportComponent5->GetComponentRotation()); FP_MainCCharacter->GetController()->SetControlRotation(PlayerTeleportComponent5->GetComponentRotation()); CaveManage->Cave5(); }
		if (CaveNumber == 5) { FP_MainCCharacter->SetActorLocationAndRotation(PlayerTeleportComponent6->GetComponentLocation(), PlayerTeleportComponent6->GetComponentRotation()); FP_MainCCharacter->GetController()->SetControlRotation(PlayerTeleportComponent6->GetComponentRotation()); CaveManage->Cave6();
		}


		//FP_MainCCharacter->SetActorLocation(PlayerTeleportComponent->GetComponentLocation()); //Testing
		FP_MainCCharacter->BAtSurface = false;
		FP_MainCCharacter->BInCaveFight = true;
		PreviousCaveNumber = CaveNumber;

		CaveManage->ResetOre();
}

/*
void ATeleporter::TeleportToBoss()
{
	FP_MainCCharacter->SetActorLocationAndRotation(TeleportToBoss1->GetComponentLocation(), TeleportToBoss1->GetComponentRotation()); FP_MainCCharacter->BInCaveFight = true;
}*/

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (FP_MainCCharacter->BInCaveFight==false) 
	{
		if (OtherActor == FP_MainCCharacter) { TeleportFromCave(); }
	}
}
/*
void ATeleporter::OnOverlapBeginBoss(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("2")));
		if (OtherActor == FP_MainCCharacter) { FP_MainCCharacter->SetActorLocationAndRotation(TeleportToBoss1->GetComponentLocation(), TeleportToBoss1->GetComponentRotation()); FP_MainCCharacter->BInCaveFight = true;}
	
}*/
