// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "FP_MainCCharacter.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "RockProjectile.h"
#include "MegaAttackProjectile.h"
#include "GolemC.generated.h"

UCLASS()
class FP_MAINC_API AGolemC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGolemC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fight) //Stats for derrived classes
		bool BHasShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fight) //Stats for derrived classes
		bool BIsOverlappingPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fight) //Stats for derrived classes
		int IntMegaAttackReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fight)
		FRotator RotatorMegaAttack;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		//TSubclassOf<class ASpitterProjectile> SpitterProjectileBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FCurrentLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FPlayerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float PlayerActorDistance;


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* MySphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnBullet)
		USceneComponent* SpawnBullet;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class ARockProjectile> RockProjectile;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class AMegaAttackProjectile> MegaProjectile;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Fight)
		void GolemGetHit(float FGolemHitDamage);

	UFUNCTION(BlueprintCallable, Category = Fight)
		void GolemThrowStone();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void GolemSlam();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void GolemMegaAttack();

	class AFP_MainCCharacter* FP_MainCCharacter;
};
