// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExplodingOre.h"
#include "Components/SphereComponent.h"

class USceneComponent;

// Sets default values
AMyExplodingOre::AMyExplodingOre()
{

	  ExpOreTime = 20.f;
	 ExpPrimed = false;
	 TickTimerOre = 0.f;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("Hey Im Ore!")));


	/** Mesh Component */
	MyExplodingOreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyExplodingOreMesh"));
	RootComponent = MyExplodingOreMesh;


	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(100.f);
	MySphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = MySphereComponent;

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyExplodingOre::OnOverlapBegin);


}
     //bool ExpPrimed = false;
	 //float TickTimerOre = 0.f; 

// Called when the game starts or when spawned
void AMyExplodingOre::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyExplodingOre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ExpPrimed == true)
	{
		TickTimerOre = TickTimerOre + 0.1f;
		if (TickTimerOre > ExpOreTime)
		{

			//ExpPrimed = false;
		    //TickTimerOre = 0.f;
			AMyExplodingOre::Destroy();
		}
	}
}

void AMyExplodingOre::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("AHGHHHH!!")));
	ExpPrimed = true;



	//FTimerHandle UnusedHandle;
	//GetWorldTimerManager().SetTimer(UnusedHandle, this, &AOreB::DestroyThis, 6.0f, false);

}
