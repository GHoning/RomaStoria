

#pragma once

#include "GameFramework/HUD.h"
#include "ItemPickUp.h"
#include "MyFPSHUD.generated.h"

/**
 * 
 */
USTRUCT()
struct FMyFPSHUDButtonStruct
{
	GENERATED_USTRUCT_BODY()

	int32 type;
	FString toolTip;
	float minX;
	float maxX;
	float minY;
	float maxY;

	FMyFPSHUDButtonStruct()
	{
		type = -1;
		toolTip = "";
		minX = 0;
		maxX = 0;
		minY = 0;
		maxY = 0;
	}
};

UCLASS()
class ROMASTORIA_API AMyFPSHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	/* Font Verdana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UFont* VerdanaFont;

	/* Unreal Font */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UFont* UE4Font;

	/* Font Scaling used by HUD Code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		float DefaultFontScale;

	/*Font scaling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		float GlobalHUDMult;



	//Clean up from here and write new one

	//Cursors

	/*Cursor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture2D* CursorMain;

	/*Hovering*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture2D* CursorHoveringButton;



	//Butons and events

	/*Buton*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture2D* ButtonBackground;
	/*Events*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UMaterialInterface* MaterialBackground;


	// Bools

	/*Draw HUD?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		bool DontDrawHUD;

	/* Draw Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		bool DontDrawMenu;


	/* InventorySlot Graphic */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture2D* InventorySlot;

	/* Amount of InventoryHUD slots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		int32 InventorySlots;


	/*Cursor*/
public:
	FVector2D MouseLocation;
	void DrawHUD_DrawCursor();

	/*Buttons*/
public:
	TArray<FMyFPSHUDButtonStruct> ButtonsMain;
	TArray<FMyFPSHUDButtonStruct> ButtonsConfirm;

	/*Cursor in buttons*/
	void DrawHUD_CheckCursorInButtons();
	void CheckCursorInButtonsMain();
	void CheckCursorInButtonsConfirm();

	const FMyFPSHUDButtonStruct* CurCheckButton;
	int32 CheckCursorInButton(const TArray<FMyFPSHUDButtonStruct>& ButtonArray);
	int32 ClickedButtonType;

	/*States*/
	bool ConfirmDialogOpen;
	bool InMainMenu;

	int32 ActiveButton_Type;
	FString ActiveButton_Tip;
	bool CursorHoveringInButton;

	/*Colors*/
public:
	const FLinearColor* ColorPtr;
	static const FColor FColorBlack;
	static const FColor FColorRed;
	static const FColor FColorYellow;
	static const FColor FColorBlue;
	static const FColor FColor_White;

	static const FLinearColor LC_Black;
	static const FLinearColor LC_Pink;
	static const FLinearColor LC_Red;
	static const FLinearColor LC_Yellow;

	/*FString*/
public:
	/*Titles*/
	static const FString S_Title_Main;
	static const FString S_Title_Confirm;
	/*Button Text*/
	static const FString S_Button_Restart;
	static const FString S_Button_Exit;

	/*Utility*/
	/*Stop the camera from moving with the mouse*/
	FORCEINLINE void SetCursorMoveOnly(bool CursorOnly)
	{
		if (!ThePC) return;
		ThePC->SetIgnoreLookInput(CursorOnly);
	}

	/* Draw HUDLine*/
	FORCEINLINE void DrawHUDLine(const FVector2D& Start, const FVector2D& End, const FLinearColor& TheColor, const float& Thick)
	{
		if(!Canvas) return;
		FCanvasLineItem NewLine(Start, End);
		NewLine.SetColor(TheColor);
		NewLine.LineThickness = Thick;
		Canvas->DrawItem(NewLine);
	}

	/* Draw Rectangle */
	FORCEINLINE void DrawHUDRect(float x, float y, float Width, float Height, const FLinearColor& Color)
	{
		if (!Canvas) return;
		FCanvasTileItem RectItem(FVector2D(x, y), FVector2D(Width, Height), Color);
		RectItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(RectItem);
	}

	/* Draw text*/
	FORCEINLINE void DrawHUDText(UFont* TheFont, const FString& TheStr, const float& X, const float& Y, const FLinearColor& TheColor, const float& TheScale, bool DrawLineOutline = false, const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1))
	{
		if (!Canvas) return;
		FCanvasTextItem NewText(FVector2D(X, Y), FText::FromString(TheStr), TheFont, TheColor);
		NewText.Scale.Set(TheScale, TheScale);
		NewText.bOutlined = true;
		NewText.OutlineColor = OutlineColor;
		NewText.OutlineColor.A = TheColor.A * 2;
		Canvas->DrawItem(NewText);
	}

	/* Draw Full Size Tile */
	FORCEINLINE void DrawFullSizeTile(UTexture2D* tex, float x, float y, const FColor& Color)
	{
		if (!Canvas) return;
		if (!tex) return;

		Canvas->SetDrawColor(Color);
		Canvas->DrawTile(tex, x, y, tex->GetSurfaceWidth(), tex->GetSurfaceHeight(), 0, 0, tex->GetSurfaceWidth(), tex->GetSurfaceHeight(), BLEND_Translucent);
	}

	FORCEINLINE void VDrawTile(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;

		Canvas->SetDrawColor(TheColor);
		Canvas->DrawTile(tex, x, y, screenX, screenY, 0, 0, tex->GetSurfaceWidth(), tex->GetSurfaceHeight(), BLEND_Translucent);
	}

public:
	void DrawHUD_DrawDialogs();

	/* Menus */
	void DrawMainMenu();
	void DrawConfirm();

	/* Buttons */
	void DrawMainMenuButtons();
	void DrawConfirmButtons();
	void DrawToolTip();

	/* Inventory */
	void DrawInventorySlots();
	void DrawInventoryItems(int32 length);

	APlayerController* ThePC;
	void PlayerInputChecks();

protected:
	/* Draw HUD */
	void DrawHUD_Reset();
	virtual void DrawHUD() override;
	virtual void PostInitializeComponents() override;

private:
	/* Crosshair Asset pointer */
	UTexture2D* CrosshairTex;
	
};
