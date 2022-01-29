// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WolfMonst.h"
#include "Spitter.h"
#include "SlimeC.h"
#include "GolemC.h"
#include "CoreMinimal.h"
#include "FP_MainCCharacter.h"
#include "GameFramework/Actor.h"
#include "CaveManage.generated.h"

UCLASS()
class FP_MAINC_API ACaveManage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaveManage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class AWolfMonst> WolfBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class ASpitter> SpitterBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class ASlimeC> Slime4BP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class ASlimeC> Slime3BP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class AGolemC> GolemBP;



	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* RootComponentCave;


	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* CaveMain;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	USceneComponent* CaveEnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* CaveEnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* CaveEnemySpawn3;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave2Main;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave2EnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave2EnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave2EnemySpawn3;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave3Main;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave3EnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave3EnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave3EnemySpawn3;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave3EnemySpawn4;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave4Main;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave4EnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave4EnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave4EnemySpawn3;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave4EnemySpawn4;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave5Main;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave5EnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave5EnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave5EnemySpawn3;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave5EnemySpawn4;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6Main;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6EnemySpawn;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6EnemySpawn2;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6EnemySpawn3;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6EnemySpawn4;
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
		USceneComponent* Cave6EnemySpawn5;


	UPROPERTY(EditAnywhere, Category = SpawnBoss)
		USceneComponent* BossSpawn;

	TArray<AActor*> FoundActors; //for holding Wolf
	TArray<AActor*> FoundActors2;//for holding spitter
	TArray<AActor*> FoundActors3;//for Slimes3
	TArray<AActor*> FoundActors4;//for SLimes4
	//TArray<AActor*>& AllOre;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Start)
		void ResetOre();

	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave1();
	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave2();
	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave3();
	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave4();
	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave5();
	UFUNCTION(BlueprintCallable, Category = Start)
		void Cave6();

	UFUNCTION(BlueprintCallable, Category = Start)
		void GolemCaveManage();

	UFUNCTION(BlueprintCallable, Category = Start)
		void CaveReset();
	

	class AFP_MainCCharacter* FP_MainCCharacter;
};
