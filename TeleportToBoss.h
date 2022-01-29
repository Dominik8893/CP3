// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FP_MainCCharacter.h"
#include"CaveManage.h"
#include "TeleportToBoss.generated.h"

UCLASS()
class FP_MAINC_API ATeleportToBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportToBoss();


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = MoveComponent)
    USceneComponent* TeleportToBoss1;

	UPROPERTY(VisibleAnywhere)
    class UBoxComponent* Boss1;


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
		void TeleportToBoss(); 
};
