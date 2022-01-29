// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FP_MainCCharacter.h"
#include "CaveManage.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "WolfMonst.generated.h"

UCLASS()
class FP_MAINC_API AWolfMonst : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWolfMonst();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FHealth;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float WolfReceivedDamage;*/


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FCurrentLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FPlayerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float PlayerActorDistance;


	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	UFUNCTION(BlueprintCallable, Category = Reset)
		void CaveResetWolf();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void WolfGetHit(float WolfReceivedDamage);

	class AFP_MainCCharacter* FP_MainCCharacter;


};
