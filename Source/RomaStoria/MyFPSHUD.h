

#pragma once

#include "GameFramework/HUD.h"
#include "MyFPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API AMyFPSHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/* Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/* Crosshair Asset pointer */
	UTexture2D* CrosshairTex;
	
};
