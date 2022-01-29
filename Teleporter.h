// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FP_MainCCharacter.h"
#include "Teleporter.generated.h"

UCLASS()
class FP_MAINC_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent;
	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent2;
	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent3;
	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent4;
	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent5;
	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent6;


	//UPROPERTY(EditAnywhere, Category = MoveComponent)
		//USceneComponent* TeleportToBoss1;

	UPROPERTY(VisibleAnywhere, Category = Integer)
		int CaveNumber;
	UPROPERTY(VisibleAnywhere, Category = Integer)
		int PreviousCaveNumber;

	UPROPERTY(EditAnywhere, Category = Integer)
		int TestTeleport;//-1 random cave

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	 //   void OnOverlapBeginBoss(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent2;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent3;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent4;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent5;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent6;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent7;

	//UPROPERTY(VisibleAnywhere)
	//	class UBoxComponent* Boss1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPointer")
		class AFP_MainCCharacter* FP_MainCCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CaveManagePointer")
		class ACaveManage* CaveManage;

	UFUNCTION(BlueprintCallable, Category = Teleport)
		void TeleportFromCave();
/*	UFUNCTION(BlueprintCallable, Category = Teleport)
		void TeleportToBoss();*/
};
