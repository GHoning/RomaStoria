

#include "RomaStoria.h"
#include "MyFPSHUD.h"


AMyFPSHUD::AMyFPSHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set the crosshair asset pointer
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("Texture2D'/Game/crosshair.crosshair'"));
	CrosshairTex = CrosshairTexObj.Object;
}

void AMyFPSHUD::DrawHUD()
{
	Super::DrawHUD();
	// Draw very simple crosshair
	// find center of the canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	// offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight()*0.5f)) );
	// Draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
