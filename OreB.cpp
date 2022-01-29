// Fill out your copyright notice in the Description page of Project Settings.


#include "OreB.h"
#include "Components/SphereComponent.h"
#include "FP_MainCCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

class USceneComponent;


// Sets default values
AOreB::AOreB()  // The Ore for mining all values can be freely changed in the editor for fast changing
{
	
	ValueResource1 = 10.f;
	ValueResource2 = 0.0f;
	HitPoint = 4;
	RespawnTime = 20;
    
	//not player changable varbs
	 IsDest = false;
    // i = 0;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	


	/** Mesh Component */
	OreBMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OreBMesh"));
	RootComponent = OreBMesh;
	
	OreBMeshDest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OreBMeshDest"));
		
	

	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(100.f);
	MySphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = MySphereComponent;

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AOreB::OnOverlapBegin);
 
	srand(time(NULL));
}


// Called when the game starts or when spawned
void AOreB::BeginPlay()
{
	Super::BeginPlay();
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	OreBMeshDest->SetVisibility(false);
}

// Called every frame
void AOreB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOreB::Gethit()
{

	HitPoint--;
 //Setting Main Ore visibility to false and DestOre to visible giving player Money
	if (HitPoint < 1 && IsDest == false) 
	{         
		
		FP_MainCCharacter->Resource1 = FP_MainCCharacter->Resource1 + (ValueResource1 * (rand() % 9) / 10) + (ValueResource1 * 0.1);     //random Amount of money 1-10
		FP_MainCCharacter->Resource2 = FP_MainCCharacter->Resource2 + (ValueResource2 * (rand() % 9) / 10) + (ValueResource2 * 0.1);
		OreBMesh->SetVisibility(false);
		OreBMeshDest->SetVisibility(true);
		IsDest = true;	
		
	 }		
}

void AOreB::RespawnOre()
{
			IsDest = false;
			HitPoint = 4.0f;

			//setting visibility
			OreBMesh->SetVisibility(true);
			OreBMeshDest->SetVisibility(false);		
}



//Unused Function Detecting Player hitting collisionbox
void AOreB::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
 

