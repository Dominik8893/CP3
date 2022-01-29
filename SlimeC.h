// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "FP_MainCCharacter.h"
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "SlimeC.generated.h"

UCLASS()
class FP_MAINC_API ASlimeC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlimeC();

	//template<class T>;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Monster)
		TSubclassOf<class ASlimeC> Slime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float FDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	int SlimeLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		FVector FPlayerLocation;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* MySphereComponent;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


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

	class AFP_MainCCharacter* FP_MainCCharacter;

	UFUNCTION(BlueprintCallable, Category = Fight)
		void SlimeGetHit(float SlimeReceivedDamage);
	
};
