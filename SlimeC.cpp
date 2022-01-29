// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "FP_MainCCharacter.h"
#include "Components/SphereComponent.h"
#include "SlimeC.h"

// Sets default values
ASlimeC::ASlimeC() //SlimeMonsterConstructor
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SlimeLevel = 3;
	FHealth = 5;
	FDamage = 2;

	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(100.f);
	
	MySphereComponent->SetupAttachment(RootComponent);
	MySphereComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASlimeC::OnOverlapBegin);
		MySphereComponent->SetRelativeLocation(RootComponent->GetComponentLocation());

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRefer(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if (MeshRefer.Succeeded()) { Body->SetStaticMesh(MeshRefer.Object); }
	Body->SetupAttachment(RootComponent);
}

void ASlimeC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) //Deal damage to player on overlap
{
	
if (OtherActor == FP_MainCCharacter)
		{
	if (SlimeLevel == 1)
	   {
		
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ASlimeC::BeginPlay()
{

	Super::BeginPlay();
	FP_MainCCharacter = Cast<AFP_MainCCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	

}

// Called every frame
void ASlimeC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FPlayerLocation=FP_MainCCharacter->GetActorLocation();

}

// Called to bind functionality to input
void ASlimeC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASlimeC::SlimeGetHit(float SlimeReceivedDamage)
{
	FHealth = FHealth - SlimeReceivedDamage;

	
	

	if (FHealth <= 0)  // Determining what size of slime to spawn
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("SlimeDead")));

		if (Slime != nullptr)
		{
			if (SlimeLevel == 4)
			{
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (500, 0, 200), RootComponent->GetComponentRotation());
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (-250, 500, 200), RootComponent->GetComponentRotation());
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (-250, -500, 200), RootComponent->GetComponentRotation());
			}
			else if (SlimeLevel == 3)
			{
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (400, 0, 200), RootComponent->GetComponentRotation());
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (-400, 0, 200), RootComponent->GetComponentRotation());
			}
			else if (SlimeLevel == 2)
			{
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (200, 0, 100), RootComponent->GetComponentRotation());
				GetWorld()->SpawnActor<AActor>(Slime, (RootComponent->GetComponentLocation()) + (-200, 0, 100), RootComponent->GetComponentRotation());
			}
		}
		else{ GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, (TEXT("No Slime Found"))); }
		
		
		Destroy();

	}

}

