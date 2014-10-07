

#include "RomaStoria.h"
#include "MyFPSCharacter.h"
#include "MyFPSHUD.h"

#define BUTTONTYPE_MAIN_RESTART 1
#define BUTTONTYPE_MAIN_EXIT 2

#define BUTTONTYPE_CONFIRM_YES 1
#define BUTTONTYPE_CONFIRM_NO 2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColorF(Color_White);

//cursor offset
#define CURSOR_DRAW_OFFSET 3

// static constants
const FString AMyFPSHUD::S_Title_Main = FString("Roma Storia");
const FString AMyFPSHUD::S_Title_Confirm = FString("Exit Game");
const FString AMyFPSHUD::S_Button_Restart = FString("Restart");
const FString AMyFPSHUD::S_Button_Exit = FString("Exit");

//colors
const FColor AMyFPSHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AMyFPSHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AMyFPSHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AMyFPSHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AMyFPSHUD::FColor_White = FColor(255, 255, 255, 255);

//Backgrounds
const FLinearColor AMyFPSHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AMyFPSHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AMyFPSHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AMyFPSHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);

AMyFPSHUD::AMyFPSHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//drawhud
	DontDrawHUD = false;

	//states
	ConfirmDialogOpen = false;
	InMainMenu = true;

	//scale
	GlobalHUDMult = 1;
	DefaultFontScale = 0.7;

	// set the crosshair asset pointer
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("Texture2D'/Game/TexturesHUD/crosshair.crosshair'"));
	CrosshairTex = CrosshairTexObj.Object;
}

void AMyFPSHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// establish pc
	ThePC = GetOwningPlayerController();
}

//Draw dialogs
void AMyFPSHUD::DrawHUD_DrawDialogs()
{
	DrawMainMenu();
	if (ConfirmDialogOpen) DrawConfirm();
}

//Menus
void AMyFPSHUD::DrawMainMenu()
{
	//background
	DrawMaterialSimple(MaterialBackground, 10, 10, 256, 512, 1.3);
	//Menu Title
	//Draw buttons
	DrawMainMenuButtons();
}

void AMyFPSHUD::DrawConfirm()
{
	//blue rect alpha 50%
	DrawHUDRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(0, 0, 1, 0.2333));

	DrawConfirmButtons();
}

void AMyFPSHUD::DrawMainMenuButtons()
{
	//start point
	float xStart = 100;
	float yStart = 110;

	//background
	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120));

	//text
	DrawHUDText(VerdanaFont, "Restart", xStart + 30, yStart + 20, LC_Black, DefaultFontScale, true, LC_Red);

	if (ButtonsMain.Num() < 1)
	{
		FMyFPSHUDButtonStruct newButton = FMyFPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_RESTART;
		newButton.toolTip = "Restart the game";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		ButtonsMain.Add(newButton);
	}

	xStart = 100;
	yStart = 410;

	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120));
	//text
	DrawHUDText(VerdanaFont, "Exit", xStart + 55, yStart + 20, LC_Black, DefaultFontScale, true, LC_Red);

	if (ButtonsMain.Num() < 2)
	{
		FMyFPSHUDButtonStruct newButton = FMyFPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_EXIT;
		newButton.toolTip = "Exit the game";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		ButtonsMain.Add(newButton);
	}
}

void AMyFPSHUD::DrawConfirmButtons()
{
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//highlighted
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Pink;
	else ColorPtr = &LC_Yellow;

	//text
	DrawHUDText(VerdanaFont, "Yes", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsConfirm.Num() < 1) {
		FMyFPSHUDButtonStruct newButton = FMyFPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_YES;
		newButton.toolTip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		ButtonsConfirm.Add(newButton);
	}

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Black;
	else ColorPtr = &LC_Yellow;

	//Text
	DrawHUDText(
		VerdanaFont, "No", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsConfirm.Num() < 2)
	{
		FMyFPSHUDButtonStruct newButton = FMyFPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_NO;
		newButton.toolTip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//could use GetTextSize to streamline this
		ButtonsConfirm.Add(newButton);
	}
}

int32 AMyFPSHUD::CheckCursorInButton(const TArray<FMyFPSHUDButtonStruct>& ButtonArray)
{
	for (int32 b = 0; b < ButtonArray.Num(); b++)
	{
		CurCheckButton = &ButtonArray[b];

		//check cursor in bounds
		if (CurCheckButton->minX <= MouseLocation.X && MouseLocation.X <= CurCheckButton->maxX &&
			CurCheckButton->minY <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->maxY)
		{

			//Active Button Type
			ActiveButton_Type = CurCheckButton->type;

			//Tool Tip
			ActiveButton_Tip = CurCheckButton->toolTip;

			//Change Cursor
			CursorHoveringInButton = true;

			//Mouse Clicked?
			if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				return ActiveButton_Type;
				//~~
				//no need to check rest of buttons
			}
		}
	}

	//No Click Occurred This Tick
	return -1;
}

//Check Confirm
void AMyFPSHUD::CheckCursorInButtonsConfirm()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type

	if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
	{
		ThePC->ConsoleCommand("Exit");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
	{
		ConfirmDialogOpen = false;
		ButtonsConfirm.Empty(); //Buttons not needed anymore
		return;
	}
}

//Check Buttons
void AMyFPSHUD::CheckCursorInButtonsMain()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsMain);

	if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
	{
		ThePC->ConsoleCommand("RestartLevel");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	{
		ConfirmDialogOpen = true;
		return;
	}
}

void AMyFPSHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		//Take Focus Away From All Other buttons
		return;
		//~
	}

	//Main
	CheckCursorInButtonsMain();
}

void AMyFPSHUD::DrawToolTip()
{
	//if mouse is too far to right, draw from left instead
	float xStart = MouseLocation.X + 150;
	float yStart = MouseLocation.Y + 5;

	//out vars
	float RV_xLength;
	float RV_yLength;
	//Text Size
	GetTextSize(
		ActiveButton_Tip,
		RV_xLength,
		RV_yLength,
		UE4Font,
		DefaultFontScale * 2
		);

	// Decide Draw to Left or to the Right 

	//Draw to the Left
	if (xStart + RV_xLength >= Canvas->SizeX - 40)
	{
		xStart -= 150 + 140 + 64 + RV_xLength;

		//If Text is too long, bring it closer to the cursor
		if (xStart < 33) xStart = 33;
	}

	//Background
	DrawHUDRect(
		xStart, yStart,
		RV_xLength + 70,
		80,
		FLinearColor(0, 0, 1, 0.7) //alpha 0.7
		);

	//Tool Tip
	DrawText(
		ActiveButton_Tip,
		LC_Pink,
		xStart + 32, yStart + 20,
		UE4Font,
		DefaultFontScale * 2,
		false		//scale position of message with HUD scale
		);
}

void AMyFPSHUD::DrawInventorySlots()
{
	float x = Canvas->SizeX / 2 - (InventorySpace->GetSurfaceWidth() * (InventorySlots/2));
	float y = Canvas->SizeY - InventorySpace->GetSurfaceHeight();
	

	for (int i = 0; i < InventorySlots; i++)
	{
		DrawFullSizeTile(InventorySpace, x, y, FColor_White);
		x = x + InventorySpace->GetSurfaceWidth();
	}
}

void AMyFPSHUD::DrawInventoryItems(TArray<AItemPickUp*>* Inventory)
{
	float x = Canvas->SizeX / 2 - (ItemIcon->GetSurfaceWidth()) - ((InventorySpace->GetSurfaceWidth() - ItemIcon->GetSurfaceWidth()) / 2);;
	float y = Canvas->SizeY - ItemIcon->GetSurfaceHeight() - ( (InventorySpace->GetSurfaceHeight() - ItemIcon->GetSurfaceHeight())/2 );

	for (int i = 0; i < Inventory->Num(); i++)
	{
		/*DrawFullSizeTile(ItemIcon, x, y, FColor_White);
		x = x + InventorySpace->GetSurfaceWidth();*/
	}
	
}

void AMyFPSHUD::DrawHUD_DrawCursor()
{
	//Tool Tip
	if (ActiveButton_Tip != "") DrawToolTip();

	//Cursor Hovering in a Button?
	if (CursorHoveringInButton)
	{
		//pointer tex found?
		if (!CursorHoveringButton) return;
		DrawFullSizeTile(CursorHoveringButton, MouseLocation.X - CURSOR_DRAW_OFFSET, MouseLocation.Y - CURSOR_DRAW_OFFSET, FColor_White);
	}

	else
	{
		//cursor tex found?
		if (!CursorMain) return;
		DrawFullSizeTile(CursorMain, MouseLocation.X - CURSOR_DRAW_OFFSET, MouseLocation.Y - CURSOR_DRAW_OFFSET, FColor_White);
	}
}

void AMyFPSHUD::PlayerInputChecks()
{
	//check out this tutorial for a list of all EKeys::
	//http://forums.epicgames.com/threads/972861-Tutorials-C-for-UE4-Code-Samples-gt-gt-New-Video-Freeze-Render-When-Tabbed-Out?p=31660286&viewfull=1#post31660286

	if (ThePC->WasInputKeyJustPressed(EKeys::Escape))
	{
		SetCursorMoveOnly(false);
		return;
	}
	if (ThePC->WasInputKeyJustPressed(EKeys::F))
	{
		SetCursorMoveOnly(!ThePC->IsLookInputIgnored());
		return;
	}
	if (ThePC->WasInputKeyJustPressed(EKeys::H))
	{
		DontDrawHUD = !DontDrawHUD;
		return;
	}
	
	//Confirm
	if (ConfirmDialogOpen)
	{
		if (ThePC->WasInputKeyJustPressed(EKeys::Y))
		{
			ThePC->ConsoleCommand("Exit");
			//could replace with function based on confirm context

			return;
		}
		if (ThePC->WasInputKeyJustPressed(EKeys::N))
		{
			ConfirmDialogOpen = false;
			ButtonsConfirm.Empty(); //Buttons not needed anymore
			//Cancel Confirm

			return;
		}
	}
}

void AMyFPSHUD::DrawHUD_Reset()
{
	ActiveButton_Type = -1;
	ActiveButton_Tip = "";
	CursorHoveringInButton = false;
}

void AMyFPSHUD::DrawHUD()
{
	//==============================
	//==============================
	//==============================
	//Have PC for Input Checks and Mouse Cursor?
	if (!ThePC)
	{
		//Attempt to Reacquire PC
		ThePC = GetOwningPlayerController();

		//Could Not Obtain PC
		if (!ThePC) return;
		//~~
	}

	//Multiplayer Safety Check
	if (!ThePC->PlayerInput) return; //not valid for first seconds of a multiplayer client
	//~~
	//==============================
	//==============================
	//==============================

	//Player Input
	PlayerInputChecks();

	//Draw HUD?
	if (DontDrawHUD) return;
	//~~

	//Super
	Super::DrawHUD();

	//No Canvas?
	if (!Canvas) return;
	//

	//Reset States
	DrawHUD_Reset();

	//================
	//Get New Mouse Position
	//================
	ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);

	//Cursor In Buttons
	DrawHUD_CheckCursorInButtons();

	//Draw Dialogs
	DrawHUD_DrawDialogs();

	//Draw Inventory slots and items
	DrawInventorySlots();
	//Get player->Inventory
	//AMyFPSCharacter Player = Cast<AMyFPSCharacter(GetWorld->GetActor->)
	
	/*AFPSHUD* MyHUD = Cast<AFPSHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MyHUD->MyBooleanVariable = true;*/
	
	

	

	//### Do Last ###
	//Draw Cursor
	DrawHUD_DrawCursor();

	//Debugging Info
	//ThePC->ClientMessage("HUD Loop Completed!");

	// Draw very simple crosshair
	// find center of the canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	// offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight()*0.5f)));

	// Draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
