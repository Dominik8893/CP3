// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FP_MainCCharacter.h"
#include "SpitterProjectile.h"
#include "Spitter.generated.h"

UCLASS()
class FP_MAINC_API ASpitter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpitter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		bool BHasShot;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float WolfReceivedDamage;*/


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class ASpitterProjectile> SpitterProjectileBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FCurrentLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FPlayerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float PlayerActorDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnBullet)
		USceneComponent* SpawnBullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnBullet)
		USceneComponent* SpawnBullet2;

	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;

	




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle SpitHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Reset)
		void CaveResetSpitter();

	UFUNCTION(BlueprintCallable, Category = Reset)
		void ResetSpitTimer();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void SpitterGetHit(float WolfReceivedDamage);

	UFUNCTION(BlueprintCallable, Category = Fight)
		void ShootSpitter();

	class AFP_MainCCharacter* FP_MainCCharacter;

};
