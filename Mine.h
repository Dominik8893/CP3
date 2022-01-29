// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Engine/GameInstance.h"
#include "Mine.generated.h"

UCLASS()
class FP_MAINC_API AMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine();

	//class UGameInstance : AMine* MineB;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
		int LevelMine;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DigAmount)
		int Revenue;

	



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DigAmount)
		int StoredRevenue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DigAmount)
	float TimeToDig; //lower = more





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DigTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	UPROPERTY(EditAnywhere, Category = "MineMesh")
		UStaticMeshComponent* MineMesh;

	UFUNCTION(BlueprintCallable, Category = Mine)
	void Dig();                //Generates Money




};
