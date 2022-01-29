// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shaft.h"
#include "FP_MainCCharacter.h"
#include "Lore.generated.h"

UCLASS()
class FP_MAINC_API ALore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALore();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
		int LevelLore;

	//MainPoint
	UPROPERTY(EditAnywhere, Category = MainComponent)
	USceneComponent* MainComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		FVector LoreVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		FVector V3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		int Counter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		bool LoadingB;//Leave at false
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		int TrackDivision;//Leave at false

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float MaxLoreMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float LoreMoney;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float TransferMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float LoreResource2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float TransferResource2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float LoreResource3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Lore)
		float TransferResource3;


	//Component1
	UPROPERTY(EditAnywhere,Category= MoveComponent1)
	USceneComponent* Component1Scene;

	UPROPERTY(VisibleAnywhere, Category = MoveComponent1)
	FVector Component1Vector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveComponent1)
		bool StartingPoint; //StartingPointBool




	//Component2
	UPROPERTY(EditAnywhere, Category = MoveComponent2)
	USceneComponent* Component2Scene;

	UPROPERTY(VisibleAnywhere, Category = MoveComponent2)
	FVector Component2Vector;

	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "LoreMesh")
		UStaticMeshComponent* LoreMesh;

	UFUNCTION(BlueprintCallable, Category = Lore)
		void Ride1(); //movesBetweenPoints

	UFUNCTION(BlueprintCallable, Category = Lore)
		void LoadingFunc(); //movesBetweenPoints

	UFUNCTION(BlueprintCallable, Category = Lore)
		void UnLoadingFunc(); //movesBetweenPoints

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinePointer")
		class AShaft* Shaft; //Pointer to Shaft

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPointer")
	class AFP_MainCCharacter* FP_MainCCharacter;

};
