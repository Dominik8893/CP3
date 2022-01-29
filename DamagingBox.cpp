// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_MainCCharacter.h"
#include "Components/BoxComponent.h"
#include "DamagingBox.h"

// Sets default values
ADamagingBox::ADamagingBox() // a invisible box for damaging the player in certains areas like lava
{
	DamageToReceive = 0.0f;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamagingBox::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADamagingBox::BeginPlay()
{
	Super::BeginPlay();
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ADamagingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamagingBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == FP_MainCCharacter)
	{
		FP_MainCCharacter->ReceiveDamage(DamageToReceive);
	}
}