

#include "RomaStoria.h"
#include "MyFPSCharacter.h"
#include "RS_FPSHUD.h"


ARS_FPSHUD::ARS_FPSHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ARS_FPSHUD::DrawHUD_Crosshair(FVector2D CrosshairPosition)
{
	FCanvasTileItem CrosshairTile(CrosshairPosition, Crosshair->Resource, FLinearColor::White);
	CrosshairTile.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(CrosshairTile);
}

void ARS_FPSHUD::DrawHUD_InventorySlot(FVector2D InventorySlotPosition)
{
	FCanvasTileItem InventorySlotTile(InventorySlotPosition, InventorySlot->Resource, FLinearColor::White);
	InventorySlotTile.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(InventorySlotTile);
}

void ARS_FPSHUD::DrawHUD_InventoryItem(FVector2D InventoryItemPosition)
{
	FCanvasTileItem InventoryItemTile(InventoryItemPosition, InventoryItem->Resource, FLinearColor::White);
	InventoryItemTile.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(InventoryItemTile);
}

void ARS_FPSHUD::DrawHUD()
{
	Super::DrawHUD();
	if (DontDrawHUD) return;
	//center off the canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	//crosshairposition
	const FVector2D CrosshairDrawPosition((Center.X - (Crosshair->GetSurfaceWidth() * 0.5f)), (Center.Y - (Crosshair->GetSurfaceHeight() * 0.5f)));
	DrawHUD_Crosshair(CrosshairDrawPosition);

	//Draw the inventorySlots
	FVector2D InventorySlotPosition(Canvas->ClipX * 0.5f - (InventorySlot->GetSurfaceWidth() * (InventorySlots * 0.5f)), Canvas->ClipY - InventorySlot->GetSurfaceHeight());

	for (int i = 0; i < InventorySlots; i++)
	{
		DrawHUD_InventorySlot(InventorySlotPosition);
		InventorySlotPosition.X = InventorySlotPosition.X + InventorySlot->GetSurfaceWidth();
	}

	AMyFPSCharacter* MyCharacter = Cast<AMyFPSCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	FVector2D InventoryItemPosition((Canvas->ClipX * 0.5f) + ((InventorySlot->GetSurfaceWidth() - InventoryItem->GetSurfaceWidth()) * 0.5f) - (InventorySlot->GetSurfaceWidth() * (InventorySlots * 0.5f)), Canvas->SizeY - InventoryItem->GetSurfaceHeight() - ((InventorySlot->GetSurfaceHeight() - InventoryItem->GetSurfaceHeight()) * 0.5f));

	for (int j = 0; j < MyCharacter->Inventory.Num(); j++)
	{
		DrawHUD_InventoryItem(InventoryItemPosition);
		InventoryItemPosition.X = InventoryItemPosition.X + InventorySlot->GetSurfaceWidth();
	}
}

