// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OreB.h"
#include "MyUserWidget.h"
#include "CaveManage.h"
#include "WolfMonst.h"
#include "Components/SpotLightComponent.h"
#include "FP_MainCCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;


UCLASS(config=Game)
class AFP_MainCCharacter : public ACharacter
{
	GENERATED_BODY()

		// Allocating Variables

         



	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */

	//UPROPERTY(EditAnywhere, Category = Mesh)
	//USkeletalMeshComponent* FP_Gun;

	//////////////////DK////////////////
//	UPROPERTY(EditAnywhere, Category = Mesh)
	//UStaticMeshComponent* FP_PickAxe;

	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* FP_SkeletalPickAxe;

	//UPROPERTY(EditAnywhere, Category = Mesh)
//	UStaticMeshComponent* FP_Weapon1;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* FP_Aim;

	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* FP_Arms;

	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* FP_Revolver;




	UPROPERTY(EditAnywhere, Category = Light)
		USpotLightComponent* Light;



	/** Location on gun mesh where projectiles should spawn. */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

public:
	AFP_MainCCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FP_MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FP_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FP_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		float FP_ReceivedDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat) //Stats for derrived classes
		int ShotsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resource)
		float Resource1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resource)
		float Resource2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resource)
		float Resource3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resource)
		int BossKey1=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackRange)
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyPress)
		bool EPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool)
		bool InCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool)
		bool bLightOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool)
		bool BAtSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Int)
		int EquipedSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Bool)
		bool BInCaveFight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Resource)
		int IEnemyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int BossBeaten;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Slot)
		bool bPickAxeReady;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Slot)
		bool bRevolverReady=true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bool)
		bool bMenuKeyPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
		bool bPlayingRevolverAnim;



protected:
	virtual void BeginPlay();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(VisibleAnywhere, Category=Projectile)
	TSubclassOf<class AFP_MainCProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UAnimBlueprint* SimpleHandAnimClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	UNiagaraSystem* NiagaraParticle;
	

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	class AWolfMonst* WolfMonst;
	class ASpitter* Spitter;
	class AGolemC* Golem;
	class ASlimeC* Slime;
	class AOreB* OreB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pointer")
		class UMyUserWidget* MyUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CavePointer")
		class ACaveManage* CaveManage;

	
	//detecting Userpress
	UFUNCTION(BlueprintCallable, Category = Character)
		 void Activate();
	UFUNCTION(BlueprintCallable, Category = Character)
		 void Deactivate();
	
	UFUNCTION(BlueprintCallable, Category = Character)
		void LightOn();
	UFUNCTION(BlueprintCallable, Category = Character)
		void Unused();
	UFUNCTION(BlueprintCallable, Category = Character)
		void SwitchToPickAxe();
	UFUNCTION(BlueprintCallable, Category = Character)
		void SwitchToWeapon();


	UFUNCTION(BlueprintCallable, Category = Character)
		void ScrollWheelUp();
	UFUNCTION(BlueprintCallable, Category = Character)
		void ScrollWheelDown();

	UFUNCTION(BlueprintCallable, Category = Character)
		void SwitchSlot();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void ReceiveDamage(float ReceivedDamage);
	UFUNCTION(BlueprintCallable, Category = Fight)
		void FP_Kill();

	UFUNCTION(BlueprintCallable, Category = Fight)
		void MonsterKilled();

	
	UFUNCTION(BlueprintCallable, Category = Slot)
		void ResetRevolver();

	UFUNCTION(BlueprintCallable, Category = Slot)
		void MenuKeyPressed();
	UFUNCTION(BlueprintCallable, Category = Slot)
		void MenuKeyReleased();


	//Animation
	UFUNCTION(BlueprintCallable, Category = Slot)
		void ResetPickAxeFunction();
	UFUNCTION(BlueprintCallable, Category = Slot)
		void ResetRevolverAnim();
	

};

