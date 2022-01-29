// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainCCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Lore.h"
#include "Shaft.h"
#include "Mine.h"
#include "MySaveGame.h"
#include "GameSaver.h"

// Sets default values
AGameSaver::AGameSaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameSaver::BeginPlay()
{
	Super::BeginPlay();
	
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Lore == nullptr || Shaft == nullptr || Mine0 == nullptr || Mine1 == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("SaveGame Pointers not Set")));
	}


}

// Called every frame
void AGameSaver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameSaver::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	
	/////////////////////////////////////////////////////////////
	
	SaveGameInstance->SaveResource1 = FP_MainCCharacter->Resource1;
	SaveGameInstance->SaveResource2 = FP_MainCCharacter->Resource2;
	SaveGameInstance->SaveBossKey1 = FP_MainCCharacter->BossKey1;

	SaveGameInstance->SaveLevelLore = Lore->LevelLore;
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), SaveGameInstance->SaveLevelLore));
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), Lore->LevelLore));

	SaveGameInstance->SaveLevelShaft = Shaft->LevelShaft;
	SaveGameInstance->SaveCollectedMoney = Shaft->CollectedMoney;
	SaveGameInstance->SaveResource2Stored = Shaft->Resource2Stored;
	SaveGameInstance->SaveResource3Stored=Shaft->Resource3Stored;

	SaveGameInstance->SaveLevelMine0 = Mine0->LevelMine;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), SaveGameInstance->SaveLevelMine0));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), Mine0->LevelMine));
	SaveGameInstance->SaveStoredRevenueMine0 = Mine0->StoredRevenue;
	SaveGameInstance->SaveLevelMine1 = Mine1->LevelMine;
	SaveGameInstance->SaveStoredRevenueMine1 = Mine1->StoredRevenue;

	////////////////////////////////////////////////////////////////


	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot0"), 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("Game Saved")));
}

void AGameSaver::LoadGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("MySlot0", 0));
	///////////////////////////////////////////////////////////////

	FP_MainCCharacter->Resource1 = SaveGameInstance->SaveResource1;
	FP_MainCCharacter->Resource2 = SaveGameInstance->SaveResource2;
	FP_MainCCharacter->BossKey1 = SaveGameInstance->SaveBossKey1;

	Lore->LevelLore = SaveGameInstance->SaveLevelLore;

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), SaveGameInstance->SaveLevelLore));
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), Lore->LevelLore));

	Shaft->LevelShaft = SaveGameInstance->SaveLevelShaft;
	Shaft->CollectedMoney = SaveGameInstance->SaveCollectedMoney;
	Shaft->Resource2Stored = SaveGameInstance->SaveResource2Stored;
	Shaft->Resource3Stored = SaveGameInstance->SaveResource3Stored;

	Mine0->LevelMine = SaveGameInstance->SaveLevelMine0;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), SaveGameInstance->SaveLevelMine0));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"), Mine0->LevelMine));

	Mine0->StoredRevenue = SaveGameInstance->SaveStoredRevenueMine0;
	Mine1->LevelMine = SaveGameInstance->SaveLevelMine1;
	Mine1->StoredRevenue = SaveGameInstance->SaveStoredRevenueMine1;

	/// //////////////////////////////////////////////////////////
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("Game Loaded")));
}

