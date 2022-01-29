// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "FP_MainCCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Wolf.generated.h"

/**
 * 
 */
UCLASS()
class FP_MAINC_API AWolf : public AMonster
{
	GENERATED_BODY()
public:
	AWolf();

	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;

	
	virtual void BeginPlay();
public:
	class AFP_MainCCharacter* FP_MainCCharacter;
	
};
