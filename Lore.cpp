// Fill out your copyright notice in the Description page of Project Settings.


#include "Lore.h"
#include <Runtime/Engine/Classes/Components/SceneComponent.h>
#include "Kismet/GameplayStatics.h"
#include "Mine.h"
#include "FP_MainCCharacter.h"


FTimerHandle LoreTimer1;
FTimerHandle LoreTimer2;

// Sets default values
ALore::ALore()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	//LoreMesh
	LoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LoreMesh"));
	
	//MainComponent
	MainComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MainComponent"));
	
	RootComponent = MainComponent;
	Counter = 0;
	LoadingB = false;
	LoreMoney = 0.f;
	MaxLoreMoney = 50.f;
	TransferMoney = 0.f;
	TrackDivision = 480;
	LevelLore = 0;
		


	//Component1
	Component1Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Component1"));
	Component1Scene->SetupAttachment(RootComponent);
	Component1Vector = { 0,0,0 };
	//FVector GetComponentLocation(Component1Vector);



	//Componen2
	Component2Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Component2"));
	Component2Scene->SetupAttachment(RootComponent);
	Component2Vector = { 0,0,0 };

	StartingPoint = false;




	
}

// Called when the game starts or when spawned
void ALore::BeginPlay()
{
	Super::BeginPlay();

	//Setting Vevctors
	Component1Vector = Component1Scene->GetComponentLocation();
	Component2Vector = Component2Scene->GetComponentLocation();

	V3 = Component2Vector - Component1Vector;

	V3 = V3 / TrackDivision;

	LoreVector = Component1Vector;
	LoreMesh->SetRelativeLocation(FVector(Component1Vector)); //Setting Lore Start


	GetWorldTimerManager().SetTimer(LoreTimer1, this, &ALore::Ride1, 0.01666f, true, 2.0f);//Setting Timer
	//GetWorldTimerManager().SetTimer(LoreTimer2, this, &ALore::Ride2, 3.f, true, 2.0f);

}

// Called every frame
void ALore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALore::Ride1()
{
	if (LevelLore != 0)
	{
		Counter++;

		MaxLoreMoney = LevelLore * 10;
		
		if (Counter == TrackDivision*2) //Loading
		{
			LoadingB = true;
			LoadingFunc();
		}
		if (Counter == TrackDivision) //UnLoading
		{
			LoadingB = true;
			UnLoadingFunc();
		}




		if (Counter <= TrackDivision && LoadingB == false) {
			LoreVector = LoreVector + V3;

			LoreMesh->SetRelativeLocation(FVector(LoreVector));
		}
		else {
			if (LoadingB == false)
			{
				LoreVector = LoreVector - V3;

				LoreMesh->SetRelativeLocation(FVector(LoreVector));
			}
		}
		if (Counter > TrackDivision * 2) { Counter = 0; }

	}
}

void ALore::LoadingFunc() //Loading of Lore
{
	if(LoreMoney<MaxLoreMoney)
	{
		Cast<AShaft>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));

		if (Cast<AShaft>(Shaft) != NULL)
		{
			//Resource1
			if (Shaft->CollectedMoney <= MaxLoreMoney)   //when all resource fits in
			{
				LoreMoney = Shaft->CollectedMoney;
				Shaft->CollectedMoney = 0.f;            
			}
			else                                                      //when it does not fit all in
			{
				TransferMoney = (MaxLoreMoney - LoreMoney);
				LoreMoney = MaxLoreMoney;
				Shaft->CollectedMoney = Shaft->CollectedMoney - TransferMoney;
			}

			//Resource2
			if (Shaft->Resource2Stored <= MaxLoreMoney)   //when all resource fits in
			{
				LoreResource2 = Shaft->Resource2Stored;
				Shaft->Resource2Stored = 0.f;
			}
			else                                                      //when it does not fit all in
			{
				TransferResource2 = (MaxLoreMoney - LoreResource2);
				LoreResource2 = MaxLoreMoney;
				Shaft->Resource2Stored = Shaft->Resource2Stored - TransferResource2;
			}

			//Resource3
			if (Shaft->Resource3Stored <= MaxLoreMoney)   //when all resource fits in
			{
				LoreResource3 = Shaft->Resource3Stored;
				Shaft->Resource3Stored = 0.f;
			}
			else                                                      //when it does not fit all in
			{
				TransferResource3 = (MaxLoreMoney - LoreResource3);
				LoreResource3 = MaxLoreMoney;
				Shaft->Resource3Stored = Shaft->Resource3Stored - TransferResource3;
			}

		}
		else { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, (TEXT("CAST FAILEED"))); }
	}
	Counter++;
	LoadingB = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, (TEXT("Money in Lore: %s"), FString::FromInt(LoreMoney)));
}

void  ALore::UnLoadingFunc()
{

	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Cast<AFP_MainCCharacter>(FP_MainCCharacter) != NULL)
	{
		FP_MainCCharacter->Resource1 = FP_MainCCharacter->Resource1 + LoreMoney;
		LoreMoney = 0.f;

		FP_MainCCharacter->Resource2 = FP_MainCCharacter->Resource2 + LoreResource2;
		LoreResource2 = 0.f;

		FP_MainCCharacter->Resource3 = FP_MainCCharacter->Resource3 + LoreResource3;
		LoreResource3 = 0.f;
	}
	Counter++;
	LoadingB = false;
}
