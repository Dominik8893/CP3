// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Lore.h"
#include "Mine.h"
#include "Shaft.h"
#include "FP_MainCCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSaver.generated.h"

UCLASS()
class FP_MAINC_API AGameSaver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSaver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Saving)
		void SaveGame();
	UFUNCTION(BlueprintCallable, Category = Saving)
		void LoadGame();

	class AFP_MainCCharacter* FP_MainCCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointer")
		class ALore* Lore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointer")
		class AShaft* Shaft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointer")
		class AMine* Mine0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointer")
		class AMine* Mine1;

};
