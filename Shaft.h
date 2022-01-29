// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine.h"
#include "Shaft.generated.h"

UCLASS()
class FP_MAINC_API AShaft : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShaft();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
		int LevelShaft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shaft)
		float CollectedMoney;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shaft)
		float Resource2Stored;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shaft)
		float Resource3Stored;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Shaft)
		void CollectMine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinePointer")
	class AMine* Mine; //Pointer to Mine

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinePointer")
		class AMine* Mine2; //Pointer to Mine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinePointer")
		class AMine* Mine3; //Pointer to Mine
};
