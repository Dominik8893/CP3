// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FP_MainCHUD.generated.h"

UCLASS()
class AFP_MainCHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFP_MainCHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

