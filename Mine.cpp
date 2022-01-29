// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine.h"










// Sets default values
AMine::AMine()
{
	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	RootComponent = MineMesh;
	
	LevelMine = 0;
	Revenue = 1;

	StoredRevenue = 0;

	TimeToDig = 1.f;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMine::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DigTimer, this, &AMine::Dig, TimeToDig, true, 2.0f);//Setting Timer

}

// Called every frame
void AMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, (TEXT("%s"), FString::FromInt(StoredRevenue)));
}

void AMine::Dig()
{
	StoredRevenue = StoredRevenue + (Revenue*LevelMine);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), StoredRevenue));
}


