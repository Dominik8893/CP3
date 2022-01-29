// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfMonst.h"
#include "Spitter.h"
#include "SlimeC.h"
#include "Kismet/GameplayStatics.h"
#include "FP_MainCCharacter.h"
#include "OreB.h"
#include "CaveManage.h"
#include "Engine/World.h"

// Sets default values
ACaveManage::ACaveManage()  // Constructor of CaveManage // This Class is used for handeling all events connected with the caves like spawning enemies
{
	FString ThePath = FString(FPlatformProcess::BaseDir());

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponentCave = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CaveMain = CreateDefaultSubobject<USceneComponent>(TEXT("CaveMain"));
	CaveEnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawn 1"));            //Creating Scenecopmonents which will be used in the editor to set the spawning points of out monster instead of hardcoding them
	CaveEnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawn2"));
	CaveEnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawn3"));

	CaveMain->SetupAttachment(RootComponentCave);
	CaveEnemySpawn->SetupAttachment(CaveMain);
	CaveEnemySpawn2->SetupAttachment(CaveMain);
	CaveEnemySpawn3->SetupAttachment(CaveMain);


	Cave2Main = CreateDefaultSubobject<USceneComponent>(TEXT("Cave2Main"));
	Cave2EnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("2EnemySpawn 1"));
	Cave2EnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("2EnemySpawn2"));
	Cave2EnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("2EnemySpawn3"));

	Cave2Main->SetupAttachment(RootComponentCave);
	Cave2EnemySpawn->SetupAttachment(Cave2Main);
	Cave2EnemySpawn2->SetupAttachment(Cave2Main);
	Cave2EnemySpawn3->SetupAttachment(Cave2Main);

	Cave3Main = CreateDefaultSubobject<USceneComponent>(TEXT("Cave3Main"));
	Cave3EnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("3EnemySpawn 1"));
	Cave3EnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("3EnemySpawn2"));
	Cave3EnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("3EnemySpawn3"));
	Cave3EnemySpawn4 = CreateDefaultSubobject<USceneComponent>(TEXT("3EnemySpawn4"));

	Cave3Main->SetupAttachment(RootComponentCave);
	Cave3EnemySpawn->SetupAttachment(Cave3Main);
	Cave3EnemySpawn2->SetupAttachment(Cave3Main);
	Cave3EnemySpawn3->SetupAttachment(Cave3Main);
	Cave3EnemySpawn4->SetupAttachment(Cave3Main);

	Cave4Main = CreateDefaultSubobject<USceneComponent>(TEXT("Cave4Main"));
	Cave4EnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("4EnemySpawn 1"));
	Cave4EnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("4EnemySpawn2"));
	Cave4EnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("4EnemySpawn3"));
	Cave4EnemySpawn4 = CreateDefaultSubobject<USceneComponent>(TEXT("4EnemySpawn4"));

	Cave4Main->SetupAttachment(RootComponentCave);
	Cave4EnemySpawn->SetupAttachment(Cave4Main);
	Cave4EnemySpawn2->SetupAttachment(Cave4Main);
	Cave4EnemySpawn3->SetupAttachment(Cave4Main);
	Cave4EnemySpawn4->SetupAttachment(Cave4Main);

	Cave5Main = CreateDefaultSubobject<USceneComponent>(TEXT("Cave5Main"));
	Cave5EnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("5EnemySpawn 1"));
	Cave5EnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("5EnemySpawn2"));
	Cave5EnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("5EnemySpawn3"));
	Cave5EnemySpawn4 = CreateDefaultSubobject<USceneComponent>(TEXT("5EnemySpawn4"));

	Cave5Main->SetupAttachment(RootComponentCave);
	Cave5EnemySpawn->SetupAttachment(Cave5Main);
	Cave5EnemySpawn2->SetupAttachment(Cave5Main);
	Cave5EnemySpawn3->SetupAttachment(Cave5Main);
	Cave5EnemySpawn4->SetupAttachment(Cave5Main);

	Cave6Main = CreateDefaultSubobject<USceneComponent>(TEXT("Cave6Main"));
	Cave6EnemySpawn = CreateDefaultSubobject<USceneComponent>(TEXT("6EnemySpawn 1"));
	Cave6EnemySpawn2 = CreateDefaultSubobject<USceneComponent>(TEXT("6EnemySpawn2"));
	Cave6EnemySpawn3 = CreateDefaultSubobject<USceneComponent>(TEXT("6EnemySpawn3"));
	Cave6EnemySpawn4 = CreateDefaultSubobject<USceneComponent>(TEXT("6EnemySpawn4"));
	Cave6EnemySpawn5 = CreateDefaultSubobject<USceneComponent>(TEXT("6EnemySpawn5"));

	Cave6Main->SetupAttachment(RootComponentCave);
	Cave6EnemySpawn->SetupAttachment(Cave6Main);
	Cave6EnemySpawn2->SetupAttachment(Cave6Main);
	Cave6EnemySpawn3->SetupAttachment(Cave6Main);
	Cave6EnemySpawn4->SetupAttachment(Cave6Main);
	Cave6EnemySpawn5->SetupAttachment(Cave6Main);

	BossSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("BossSpawn"));
	BossSpawn->SetupAttachment(RootComponentCave);

}

// Called when the game starts or when spawned
void ACaveManage::BeginPlay()
{
	Super::BeginPlay();
	srand(time(NULL));
	

	try 
	{
	   if (GetWorld())
	   {
		   FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	   }
	   else {throw "Division by zero condition!";}
	}
	catch (const char* msg){};



	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (WolfBP == nullptr || SpitterBP == nullptr || Slime4BP == nullptr || Slime3BP == nullptr || GolemBP == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Some Pointers are nullptr | CaveManage")));
	}
	
	

}

// Called every frame
void ACaveManage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACaveManage::ResetOre()
{
	TArray<AActor*> AllOre;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOreB::StaticClass(), AllOre);

	if (AllOre.Num() != 0)
	{
		for (int i = 0; i < AllOre.Num(); i++) { if (AllOre[i] != NULL) {Cast<AOreB>(AllOre[i])->RespawnOre();} }
	}
	else{ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL"))); }
}

void ACaveManage::Cave1()
{
	

	int8 d = ((rand() % 2)+1);
	int16 r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (CaveEnemySpawn->GetComponentLocation())+r, CaveEnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	 d = ((rand() % 2) + 1);
	 r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (CaveEnemySpawn2->GetComponentLocation()) + r, CaveEnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }
	
	 d = ((rand() % 2) + 1);
	 r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (CaveEnemySpawn3->GetComponentLocation()) + r, CaveEnemySpawn3->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }



	
	
       //UGameplayStatics::GetAllActorsOfClass(GetWorld(),SpawnClass, FoundActors);
	   UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
}

void ACaveManage::Cave2()
{

	

	int8 d = ((rand() % 2) + 1);
	int16 r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave2EnemySpawn->GetComponentLocation()) + r, Cave2EnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 3) + 1);
	r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave2EnemySpawn2->GetComponentLocation()) + r, Cave2EnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 2) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave2EnemySpawn3->GetComponentLocation()) + r, Cave2EnemySpawn3->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpitterBP, FoundActors2);
	FoundActors.Append(FoundActors2);
}

void ACaveManage::Cave3()
{
	
	int8 d = ((rand() % 2) + 1);
	int16 r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave3EnemySpawn->GetComponentLocation()) + r, Cave3EnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 2) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave3EnemySpawn2->GetComponentLocation()) + r, Cave3EnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 2) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave3EnemySpawn3->GetComponentLocation()) + r, Cave3EnemySpawn3->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 3) + 1);
	r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave3EnemySpawn4->GetComponentLocation()) + r, Cave3EnemySpawn4->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }



	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpitterBP, FoundActors2);
	FoundActors.Append(FoundActors2);

}

void ACaveManage::Cave4()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CaveFired"))); 


	int8 d = ((rand() % 2) + 1);
	int16 r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave4EnemySpawn->GetComponentLocation()) + r, Cave4EnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 2) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave4EnemySpawn2->GetComponentLocation()) + r, Cave4EnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 2) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave4EnemySpawn3->GetComponentLocation()) + r, Cave4EnemySpawn3->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 3) + 1);
	r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave4EnemySpawn4->GetComponentLocation()) + r, Cave4EnemySpawn4->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }



	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpitterBP, FoundActors2);
	FoundActors.Append(FoundActors2);
}

void ACaveManage::Cave5()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CaveFired")));


	int8 d = ((rand() % 3) + 1);
	int16 r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave5EnemySpawn->GetComponentLocation()) + r, Cave5EnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = 1;
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave5EnemySpawn2->GetComponentLocation()) + r, Cave5EnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 3) + 1);
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave5EnemySpawn3->GetComponentLocation()) + r, Cave5EnemySpawn3->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = ((rand() % 3) + 2);
	r = (rand() % 600 - 300);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(WolfBP, (Cave5EnemySpawn4->GetComponentLocation()) + r, Cave5EnemySpawn4->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }



	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpitterBP, FoundActors2);
	FoundActors.Append(FoundActors2);
}

void ACaveManage::Cave6()
{
	int8 d = ((rand() % 2));
	int16 r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(SpitterBP, (Cave6EnemySpawn->GetComponentLocation()) + r, Cave6EnemySpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }

	d = 1;
	r = (rand() % 400 - 200);
	for (int i = 0; i < d; i++) { GetWorld()->SpawnActor<AActor>(Slime3BP, (Cave6EnemySpawn2->GetComponentLocation()) + r, Cave6EnemySpawn2->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++; }



	UGameplayStatics::GetAllActorsOfClass(GetWorld(), WolfBP, FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpitterBP, FoundActors2);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Slime3BP, FoundActors3);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Slime4BP, FoundActors4);
	FoundActors.Append(FoundActors2);
	FoundActors.Append(FoundActors3);
	FoundActors.Append(FoundActors4);

}



void ACaveManage::CaveReset()
{
	if (FoundActors.Num() != 0) 
	{
		for (int i = 0; i < FoundActors.Num(); i++) { if (FoundActors[i] != NULL) { FoundActors[i]->Destroy(); } else { GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("ACharacterWasNull"))); } }
	}
	else{ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ArrayEmpty"))); GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CaveManageAlert")));}




	FoundActors.Empty();
	
	FP_MainCCharacter->IEnemyCount = FoundActors.Num();

}

void ACaveManage::GolemCaveManage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("EnteredBoss")));

	GetWorld()->SpawnActor<AActor>(GolemBP, (BossSpawn->GetComponentLocation()), BossSpawn->GetComponentRotation()); FP_MainCCharacter->IEnemyCount++;
}
