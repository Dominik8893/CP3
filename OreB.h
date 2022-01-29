// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FP_MainCCharacter.h"
#include "OreB.generated.h"

UCLASS()
class FP_MAINC_API AOreB : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOreB();
	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Money)
		float ValueResource1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Money)
		float ValueResource2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitPoint)
		float RespawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HitPoint)
	int HitPoint;

	UPROPERTY(VisibleAnywhere, Category = HitPoint)
		bool IsDest;

	UPROPERTY(VisibleAnywhere, Category = HitPoint)
		int i;
	
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* MySphereComponent;

	


	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle OreRespawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Ore")
		UStaticMeshComponent* OreBMesh;

	UPROPERTY(EditAnywhere, Category = "Ore")
		UStaticMeshComponent* OreBMeshDest;
	
	//UPROPERTY(EditAnywhere)
	class AFP_MainCCharacter* FP_MainCCharacter;

	UFUNCTION(BlueprintCallable,Category=Attack) 
	void Gethit();  //FP hits ore

	UFUNCTION(BlueprintCallable, Category = RespawnFunction)
	void RespawnOre();
		 


	
};
