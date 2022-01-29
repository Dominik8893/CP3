// Fill out your copyright notice in the Description page of Project Settings.


#include "Shaft.h"

#include "Kismet/GameplayStatics.h"
#include "Mine.h"

FTimerHandle ShaftGoldCollect;
// Sets default values
AShaft::AShaft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LevelShaft = 1;
}

// Called when the game starts or when spawned
void AShaft::BeginPlay()
{
	Super::BeginPlay();

		GetWorldTimerManager().SetTimer(ShaftGoldCollect, this, &AShaft::CollectMine, (64.0f / LevelShaft), false, 2.0f);//Setting Timer
	
}

// Called every frame
void AShaft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), GetWorldTimerManager().GetTimerRemaining(ShaftGoldCollect)));
}

void AShaft::CollectMine()
{
	
	//OreB = Cast<AOreB>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
	if (LevelShaft == 0) {}
	else
	{
		Cast<AMine>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));

		if (Cast<AMine>(Mine) != NULL)
		{
			CollectedMoney = CollectedMoney + Mine->StoredRevenue;
			Mine->StoredRevenue = 0;			
		}
		else { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, (TEXT("CAST FAILEED"))); }

		if (Cast<AMine>(Mine2) != NULL)
		{
			Resource2Stored = Resource2Stored + Mine2->StoredRevenue;
			Mine2->StoredRevenue = 0;
		}
		else { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, (TEXT("CAST FAILEED"))); }

	}

	GetWorldTimerManager().SetTimer(ShaftGoldCollect, this, &AShaft::CollectMine, (64.0f / LevelShaft), false, (64.0f / LevelShaft));
}

