// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_MainCGameMode.h"
#include "FP_MainCHUD.h"
#include "FP_MainCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFP_MainCGameMode::AFP_MainCGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFP_MainCHUD::StaticClass();
}
