// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_MainCCharacter.h"
#include "FP_MainCProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "OreB.h"
#include "MyUserWidget.h"
#include "CaveManage.h"
#include "WolfMonst.h"
#include "Spitter.h"
#include "SlimeC.h"
#include "GolemC.h"
#include "Components/SpotLightComponent.h"
#include "DrawDebugHelpers.h"

//#define elif else if;

FTimerHandle ResetPickAxe;
FTimerHandle RevolverReady;
FTimerHandle RevolverAnimReady;
FTimerHandle RevolverAnimReset;

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFP_MainCCharacter

AFP_MainCCharacter::AFP_MainCCharacter() // Constructor of the player character // all base logic for the character is handeled here
{
	ShotsLeft=5;
	Resource1=0.f;
	Range = 300.f;
	bLightOn = false;
	bPickAxeReady = true;
	EquipedSlot = 0;
	BInCaveFight = false;
	BAtSurface = true;

	FP_Damage = 2;
	FP_MaxHealth = 20;
	FP_Health = 20;
	BossBeaten = 0;
	bMenuKeyPressed = false;

	IEnemyCount = 0;



	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	


	//DK//
	FP_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	FP_Arms->SetOnlyOwnerSee(false);
	FP_Arms->bCastDynamicShadow = false;
	FP_Arms->CastShadow = false;
	FP_Arms->SetupAttachment(FirstPersonCameraComponent);


	FP_Revolver = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Revolver"));
	FP_Revolver->SetOnlyOwnerSee(false);
	FP_Revolver->bCastDynamicShadow = false;
	FP_Revolver->CastShadow = false;
	FP_Revolver->SetupAttachment(FP_Arms, TEXT("RightArm_Socket"));

	

	FP_SkeletalPickAxe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_SkeletalPickAxe"));
	FP_SkeletalPickAxe->SetOnlyOwnerSee(false);
	FP_SkeletalPickAxe->bCastDynamicShadow = false;
	FP_SkeletalPickAxe->CastShadow = false;
	FP_SkeletalPickAxe->SetupAttachment(FP_Arms, TEXT("RightArm_Socket"));


	FP_Aim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FP_Aim"));
	FP_Aim->SetOnlyOwnerSee(false);
	FP_Aim->bCastDynamicShadow = false;
	FP_Aim->CastShadow = false;
	FP_Aim->SetupAttachment(FirstPersonCameraComponent);

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("FP_Light"));
	Light->SetupAttachment(FirstPersonCameraComponent);

	//FP_Weapon1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FP_Weapon"));
	//FP_Weapon1->SetupAttachment(FP_Arms, TEXT("RightArm_Socket"));




	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(FP_Gun);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	/*
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.
	*/
	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	//Particles

	
}

void AFP_MainCCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Light->SetVisibility(false);
	//FP_Weapon1->SetVisibility(false);
	FP_Revolver->SetVisibility(false);
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	//UMyUserWidget::Initialize();





	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		//VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		//VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}



////////////////////////////////////////        Tick         /////////////////////////////////////
 int Ticker=0;

void AFP_MainCCharacter::Tick(float DeltaTime)
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Amount of Money: %f"),Cash);
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("Hello %s"), *GetActorLocation().ToString()));
	// 
	//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Turquoise,(TEXT("CASH:"), FString::FromInt(Cash)));
	
}







//////////////////////////////////////////////////////////////////////////
// Input

void AFP_MainCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)  // Binding Keys to diffrent actions
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	//Bind Activate events
	PlayerInputComponent->BindAction("Activate", IE_Pressed, this, &AFP_MainCCharacter::Activate);
	PlayerInputComponent->BindAction("Activate", IE_Released, this, &AFP_MainCCharacter::Deactivate);

	PlayerInputComponent->BindAction("LightOpt", IE_Pressed, this, &AFP_MainCCharacter::LightOn);
	PlayerInputComponent->BindAction("TestInp", IE_Pressed, this, &AFP_MainCCharacter::Unused);

	PlayerInputComponent->BindAction("SwitchToPickAxe", IE_Pressed, this, &AFP_MainCCharacter::SwitchToPickAxe);
	
	PlayerInputComponent->BindAction("SwitchToWeapon", IE_Pressed, this, &AFP_MainCCharacter::SwitchToWeapon);

	PlayerInputComponent->BindAction("ScrollWheelUp", IE_Pressed, this, &AFP_MainCCharacter::ScrollWheelUp);
	PlayerInputComponent->BindAction("ScrollWheelDown", IE_Pressed, this, &AFP_MainCCharacter::ScrollWheelDown);

	//Bring Menu Up
	PlayerInputComponent->BindAction("BringUpMenu", IE_Pressed, this, &AFP_MainCCharacter::MenuKeyPressed);
	PlayerInputComponent->BindAction("BringUpMenu", IE_Released, this, &AFP_MainCCharacter::MenuKeyReleased);
	
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFP_MainCCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFP_MainCCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_MainCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_MainCCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFP_MainCCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFP_MainCCharacter::LookUpAtRate);
}

void AFP_MainCCharacter::OnFire()   // LeftClick Action like shooting or mining
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("bang bang!!")));  //Check if onFire is working



	switch (EquipedSlot) {

	case 0:
	{


		if (bPickAxeReady == true)
		{
			bPickAxeReady = false;

			

			FP_SkeletalPickAxe->SetRelativeLocation(FVector(-0.05f, -0.0f, -0.01f));
			FP_SkeletalPickAxe->SetRelativeRotation(FRotator(25.80f, 59.66f, 77.0f));


//RayCast for Determining whats in front of us

			FHitResult OutHit;
			FVector Start = FP_Aim->GetComponentLocation();
			FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
			FVector End = ((ForwardVector * Range) + Start);
			FCollisionQueryParams CollisionParams;

			//DrawDebugLine(GetWorld(), Start, End, FColor::Green,1,0,0,3); DebugLineAttack

			bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

			if (IsHit)
			{
				if (OutHit.bBlockingHit)
				{



					//Display various things about Hit
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("bang bang!!")));  //Check if onFire is working
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,   (TEXT("%s"), *OutHit.GetActor()->GetName()));
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("%s"), *OutHit.ImpactPoint.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,  (TEXT("%s"), *OutHit.ImpactNormal.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue,  (TEXT("%s"), OutHit.ToString()));



					AActor* TheOre = OutHit.GetActor();
					//AOreB* OreB = Cast<AOreB>(TheOre);
					//OreB->Gethit();

					if (Cast<AOreB>(TheOre) == OutHit.GetActor()) {
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
						OreB = Cast<AOreB>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
						Cast<AOreB>(TheOre)->Gethit();
					}

				}
			}

			GetWorldTimerManager().SetTimer(ResetPickAxe, this, &AFP_MainCCharacter::ResetPickAxeFunction, 0.80f, false, 0.80f);//Setting Timer

		}
		/*
		// try and fire a projectile
		if (ProjectileClass != nullptr)
		{
			//added by user
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,(TEXT("Shoot!!")));

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				if (bUsingMotionControllers)
				{
					const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
					const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
					World->SpawnActor<AFP_MainCProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				}
				else
				{
					const FRotator SpawnRotation = GetControlRotation();

				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);


					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


					World->SpawnActor<AFP_MainCProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				}
			}
		}

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

		*/
	}
	break;
	case 1:
	{


		

		if (bRevolverReady == true) {
			

			ShotsLeft--;
			if (ShotsLeft <= 0) {
				bRevolverReady = false;
				GetWorldTimerManager().SetTimer(RevolverReady, this, &AFP_MainCCharacter::ResetRevolver, 1.20f, false, 1.20f);//Setting Timer
				
			}

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("PifPaf")));

			FHitResult OutHit;
			FVector Start = FP_Aim->GetComponentLocation();
			FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
			FVector End = ((ForwardVector * 2000) + Start);
			FCollisionQueryParams CollisionParams;

			//DrawDebugLine(GetWorld(), Start, End, FColor::Green,1,0,0,3); DebugLineAttack

			bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

			if (FireSound != nullptr) //playing sound
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
			
			//playingAnimation
			
			

			//bPlayingRevolverAnim = false;
			//GetWorldTimerManager().SetTimer(RevolverAnimReady, this, &AFP_MainCCharacter::ResetRevolverAnimReset, 0.01f, false, 0.01f);

			bRevolverReady = false;
			bPlayingRevolverAnim = true;
			GetWorldTimerManager().SetTimer(RevolverAnimReset, this, &AFP_MainCCharacter::ResetRevolverAnim, 0.50f, false, 0.50f);
			//Setting Timer
			

			if (IsHit)
			{
				if (OutHit.bBlockingHit)
				{
					//Display various things about Hit
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("bang bang!!")));  //Check if onFire is working
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("%s"), *OutHit.GetActor()->GetName()));
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (TEXT("%s"), *OutHit.GetActor()->GetClass()));

					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("%s"), *OutHit.ImpactPoint.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,  (TEXT("%s"), *OutHit.ImpactNormal.ToString()));
					//GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue,  (TEXT("%s"), OutHit.ToString()));


					if (OutHit.GetActor()->IsA(AWolfMonst::StaticClass()))
					{
						AActor* TheWolf = OutHit.GetActor();
						if (Cast<AWolfMonst>(TheWolf) == OutHit.GetActor())
						{
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
							WolfMonst = Cast<AWolfMonst>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
							Cast<AWolfMonst>(TheWolf)->WolfGetHit(FP_Damage);
						}
					}
					else if(OutHit.GetActor()->IsA(ASpitter::StaticClass()))
						{
							AActor* TheSpitter = OutHit.GetActor();
							if (Cast<ASpitter>(TheSpitter) == OutHit.GetActor())
							{
								//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
								Spitter = Cast<ASpitter>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
								Cast<ASpitter>(TheSpitter)->SpitterGetHit(FP_Damage);
							}
						}

						else if (OutHit.GetActor()->IsA(AGolemC::StaticClass()))
						{
								AActor* TheGolem = OutHit.GetActor();
								if (Cast<AGolemC>(TheGolem) == OutHit.GetActor())
								{
									//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
									Golem = Cast<AGolemC>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
									Cast<AGolemC>(TheGolem)->GolemGetHit(FP_Damage);
									GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("HitGolem")));
								}
					
					     }


						else if(OutHit.GetActor()->IsA(ASlimeC::StaticClass()))
					{
						AActor* TheSlime = OutHit.GetActor();
						if (Cast<ASlimeC>(TheSlime) == OutHit.GetActor())
						{
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
							Slime = Cast<ASlimeC>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
							Cast<ASlimeC>(TheSlime)->SlimeGetHit(FP_Damage);
							GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("HitSlime")));
						}

					}
							
					//	else { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("NotGolemHit"))); }
						





					/*
					if (OutHit.GetActor()->IsA(AWolfMonst::StaticClass()))
					{
						AActor* TheWolf = OutHit.GetActor();
						if (Cast<AWolfMonst>(TheWolf) == OutHit.GetActor())
						{
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
							WolfMonst = Cast<AWolfMonst>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
							Cast<AWolfMonst>(TheWolf)->WolfGetHit(FP_Damage);
						}
					}
					else
					{
						if (OutHit.GetActor()->IsA(ASpitter::StaticClass()))
						{
							AActor* TheSpitter = OutHit.GetActor();
							if (Cast<ASpitter>(TheSpitter) == OutHit.GetActor())
							{
								//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
								Spitter = Cast<ASpitter>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
								Cast<ASpitter>(TheSpitter)->SpitterGetHit(FP_Damage);
							}
						}
						else
						{
							if (OutHit.GetActor()->IsA(AGolemC::StaticClass()))
							{
								AActor* TheGolem = OutHit.GetActor();
								if (Cast<AGolemC>(TheGolem) == OutHit.GetActor())
								{
										//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("CompareFired")));
										Golem = Cast<AGolemC>(UGameplayStatics::GetActorOfClass(GetWorld(), 0));
										Cast<AGolemC>(TheGolem)->GolemGetHit(FP_Damage);
										GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("HitGolem")));
								}
					
							}else{ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("NotGolemHit"))); }
						}
					}

					*/

				}
			}
		}
	}
	break;
	case 2:
	{

	}
	break;
	}
}

void AFP_MainCCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFP_MainCCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AFP_MainCCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AFP_MainCCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AFP_MainCCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFP_MainCCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFP_MainCCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFP_MainCCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AFP_MainCCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFP_MainCCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AFP_MainCCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AFP_MainCCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

void AFP_MainCCharacter::Activate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("Activated")));
	EPressed = true;
}

void AFP_MainCCharacter::Deactivate()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("Deactivated")));
	EPressed = false;
}

void AFP_MainCCharacter::LightOn()
{
	if (bLightOn == false)
	{
		Light->SetVisibility(true);
		bLightOn = true;
	}
	else
	{
		Light->SetVisibility(false);
		bLightOn = false;
	}
}

void AFP_MainCCharacter::Unused()
{
}

void AFP_MainCCharacter::SwitchToPickAxe()
{
	EquipedSlot = 0;
	SwitchSlot();
}

void AFP_MainCCharacter::SwitchToWeapon()
{
	EquipedSlot = 1;
    SwitchSlot();	
}

void AFP_MainCCharacter::ScrollWheelUp()
{
	if (EquipedSlot >= 2) { EquipedSlot = 0; } 
	else { EquipedSlot++; }
	SwitchSlot();
}

void AFP_MainCCharacter::ScrollWheelDown()
{
	if (EquipedSlot <= 0) { EquipedSlot = 2; } //Amount of slots -1
	else { EquipedSlot--; }
	SwitchSlot();
}

void AFP_MainCCharacter::SwitchSlot()
{
	FP_Revolver->SetVisibility(false);
	FP_SkeletalPickAxe->SetVisibility(false);
	//FP_Weapon1->SetVisibility(false);

	switch (EquipedSlot)
	{
	case 0: {FP_SkeletalPickAxe->SetVisibility(true); break;}
	case 1: {FP_Revolver->SetVisibility(true); break;}
	//case 2: {FP_Weapon1->SetVisibility(true); break; }




	}
}

void AFP_MainCCharacter::ReceiveDamage(float ReceivedDamage)
{
	FP_Health = FP_Health - ReceivedDamage;

	if (FP_Health <= 0) { FP_Kill(); }

}

void AFP_MainCCharacter::FP_Kill()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, (TEXT("Killed")));
	SetActorLocation({ -3500,1100,450 });
	BInCaveFight = false;
	BAtSurface = true;

	FP_Health = FP_MaxHealth;

	CaveManage->CaveReset();

}

void AFP_MainCCharacter::MonsterKilled()
{
	
	IEnemyCount--;
GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%d"),IEnemyCount));
	if (IEnemyCount == 0) { BInCaveFight = false; GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, FString::Printf(TEXT("NotInFight")));
	}
}

void AFP_MainCCharacter::ResetPickAxeFunction()
{
	

	// PickAxeforHitting = FTransform((0.0f, 0.0f, 0.0f), (0.0f, 0.0f, 0.0f), (0.0f, 0.0f, 0.0f));
	FP_SkeletalPickAxe->SetRelativeLocation(FVector(-0.05f, -0.03f, 0.01f));
	FP_SkeletalPickAxe->SetRelativeRotation(FRotator(43.80f, 27.26f, 80.12));
	
	bPickAxeReady = true;

	//FP_Arms->PlayAnimation(AnimSequence'/Game/Geometry/Hands/Animation/PickAxeHitting.PickAxeHitting', false);
}

void AFP_MainCCharacter::ResetRevolver()
{
	bRevolverReady = true;
	ShotsLeft = 5;
}
void AFP_MainCCharacter::ResetRevolverAnim()
{
	bPlayingRevolverAnim = false;
	bRevolverReady = true;
}

void AFP_MainCCharacter::MenuKeyPressed()
{
	bMenuKeyPressed = true;
}

void AFP_MainCCharacter::MenuKeyReleased()
{
	bMenuKeyPressed = false;
}

