// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */


UCLASS()
class FP_MAINC_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UMySaveGame();
	//Character
	UPROPERTY(EditAnywhere)
		float SaveResource1;
	UPROPERTY(EditAnywhere)
		float SaveResource2;
	UPROPERTY(EditAnywhere)
		int SaveBossKey1;
	//Lore
	UPROPERTY(EditAnywhere)
		int SaveLevelLore;
	//Shaft
	UPROPERTY(EditAnywhere)
		int SaveLevelShaft;
	UPROPERTY(EditAnywhere)
		float SaveCollectedMoney;
	UPROPERTY(EditAnywhere)
		float SaveResource2Stored;
	UPROPERTY(EditAnywhere)
		float SaveResource3Stored;
	//Mine
	UPROPERTY(EditAnywhere)
		int SaveLevelMine0;
	UPROPERTY(EditAnywhere)
		int SaveStoredRevenueMine0;
	UPROPERTY(EditAnywhere)
		int SaveLevelMine1;
	UPROPERTY(EditAnywhere)
		int SaveStoredRevenueMine1;
};
