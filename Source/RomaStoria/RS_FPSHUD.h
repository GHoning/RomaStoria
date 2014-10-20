

#pragma once

#include "GameFramework/HUD.h"
#include "RS_FPSHUD.generated.h"

/**
 *	Class to describe all the elements of the HUD
 */
UCLASS()
class ROMASTORIA_API ARS_FPSHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/* The Crosshair Texture  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	UTexture2D* Crosshair;

	/* InventorySlot Texture */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	UTexture2D* InventorySlot;

	/* Number of InventorySlots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int32 InventorySlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	UTexture2D* InventoryItem;

	/* Draw hud? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	bool DontDrawHUD;

public:
	void DrawHUD_Crosshair(FVector2D CrosshairPosition);
	void DrawHUD_InventorySlot(FVector2D InventorySlotPosition);
	void DrawHUD_InventoryItem(FVector2D InventoryItemPosition);

private:
	void DrawHUD() override;
};
