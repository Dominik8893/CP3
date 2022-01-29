// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_MainCCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TeleportToMine.generated.h"

UCLASS()
class FP_MAINC_API ATeleportToMine : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	ATeleportToMine();

	UPROPERTY(EditAnywhere, Category = MoveComponent)
		USceneComponent* PlayerTeleportComponent;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* MyBoxComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AFP_MainCCharacter* FP_MainCCharacter;

};
