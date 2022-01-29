// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_MainCCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Wolf.h"

AWolf::AWolf()
{
	Health = 10;
    Damage = 2;
	 
	

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRefer(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (MeshRefer.Succeeded()) { Body->SetStaticMesh(MeshRefer.Object); }
	
}

void AWolf::BeginPlay()
{
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}