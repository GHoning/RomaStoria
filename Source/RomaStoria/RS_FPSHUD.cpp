

#include "RomaStoria.h"
#include "MyFPSCharacter.h"
#include "RS_FPSHUD.h"

#define BUTTONTYPE_MAIN_RESTART 1
#define BUTTONTYPE_MAIN_NOTEBOOK 2
#define BUTTONTYPE_MAIN_EXIT 3

#define BUTTONTYPE_CONFIRM_YES 1
#define BUTTONTYPE_CONFIRM_NO 2

#define BUTTONTYPE_NOTEBOOK_1 1
#define BUTTONTYPE_NOTEBOOK_2 2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColorF(Color_White);

//cursor offset
#define CURSOR_DRAW_OFFSET 3

// static constants
const FString ARS_FPSHUD::S_Title_Main = FString("Roma Storia");
const FString ARS_FPSHUD::S_Title_Confirm = FString("Exit Game");
const FString ARS_FPSHUD::S_Button_Restart = FString("Restart");
const FString ARS_FPSHUD::S_Button_Exit = FString("Exit");

//colors
const FColor ARS_FPSHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor ARS_FPSHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor ARS_FPSHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor ARS_FPSHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor ARS_FPSHUD::FColor_White = FColor(255, 255, 255, 255);

//Backgrounds
const FLinearColor ARS_FPSHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor ARS_FPSHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor ARS_FPSHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor ARS_FPSHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);

ARS_FPSHUD::ARS_FPSHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//drawhud
	DontDrawHUD = false;

	//states
	ConfirmNotebookOpen = false;
	ConfirmDialogOpen = false;
	InMainMenu = false;
	InComic = true;


	//scale
	GlobalHUDMult = 1;
	DefaultFontScale = 0.7;
}

void ARS_FPSHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// establish pc
	ThePC = GetOwningPlayerController();
}

//Draw dialogs
void ARS_FPSHUD::DrawHUD_DrawDialogs()
{
	DrawMainMenu();
	if (ConfirmDialogOpen) DrawConfirm();
	if (ConfirmNotebookOpen) DrawNotebook();
}

//Menus
void ARS_FPSHUD::DrawMainMenu()
{
	//background
	DrawMaterialSimple(MaterialBackground, 10, 10, 256, 512, 0);
	//Menu Title
	//Draw buttons
	DrawMainMenuButtons();
}

void ARS_FPSHUD::DrawConfirm()
{
	//blue rect alpha 50%
	DrawHUDRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(1, 1, 1, 0.2333));

	DrawConfirmButtons();
}

void ARS_FPSHUD::DrawNotebook()
{
	//blue rect alpha 50%
	DrawHUDRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(1, 1, 1, 0.2333));
	DrawNotebookButtons();
}

void ARS_FPSHUD::DrawMainMenuButtons()
{
	//start point
	float xStart = 100;
	float yStart = 110;

	//background
	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(1, 1, 1, 0.2333));

	//text
	DrawHUDText(VerdanaFont, "Restart", xStart + 30, yStart + 20, LC_Black, DefaultFontScale, true, FLinearColor(1, 1, 1, 0.2333));

	if (ButtonsMain.Num() < 1)
	{
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_RESTART;
		newButton.Tooltip = "Restart the game";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		ButtonsMain.Add(newButton);
	}

	xStart = 100;
	yStart = 210;

	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(1, 1, 1, 0.2333));
	//text
	DrawHUDText(VerdanaFont, "Notebook", xStart + 55, yStart + 20, LC_Black, DefaultFontScale, true, FLinearColor(1, 1, 1, 0.2333));

	if (ButtonsMain.Num() < 2)
	{
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_NOTEBOOK;
		newButton.Tooltip = "Open Notebook";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		ButtonsMain.Add(newButton);
	}


	xStart = 100;
	yStart = 410;

	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(1, 1, 1, 0.2333));
	//text
	DrawHUDText(VerdanaFont, "Exit", xStart + 55, yStart + 20, LC_Black, DefaultFontScale, true, FLinearColor(1, 1, 1, 0.2333));

	if (ButtonsMain.Num() < 3)
	{
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_EXIT;
		newButton.Tooltip = "Exit the game";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		ButtonsMain.Add(newButton);
	}
}

void ARS_FPSHUD::DrawConfirmButtons()
{
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//highlighted
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Yellow;
	else ColorPtr = &LC_Black;

	//text
	DrawHUDText(VerdanaFont, "Yes", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsConfirm.Num() < 1) {
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_YES;
		newButton.Tooltip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		ButtonsConfirm.Add(newButton);
	}

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Yellow;
	else ColorPtr = &LC_Black;

	//Text
	DrawHUDText(
		VerdanaFont, "No", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsConfirm.Num() < 2)
	{
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_NO;
		newButton.Tooltip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//could use GetTextSize to streamline this
		ButtonsConfirm.Add(newButton);
	}
}

void ARS_FPSHUD::DrawNotebookButtons()
{
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//highlighted
	if (ActiveButton_Type == BUTTONTYPE_NOTEBOOK_1) ColorPtr = &LC_Yellow;
	else ColorPtr = &LC_Black;

	//text
	DrawHUDText(VerdanaFont, "Note 1", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsNotebook.Num() < 1) {
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_NOTEBOOK_1;
		newButton.Tooltip = "Read Note 1";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		ButtonsNotebook.Add(newButton);
	}

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_NOTEBOOK_2) ColorPtr = &LC_Yellow;
	else ColorPtr = &LC_Black;

	//Text
	DrawHUDText(
		VerdanaFont, "Back", xStart + 30, yStart + 20, *ColorPtr, DefaultFontScale, true);

	if (ButtonsNotebook.Num() < 2)
	{
		FRS_FPSHUDButtonStruct newButton = FRS_FPSHUDButtonStruct();
		newButton.type = BUTTONTYPE_NOTEBOOK_2;
		newButton.Tooltip = "Return to menu";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//could use GetTextSize to streamline this
		ButtonsNotebook.Add(newButton);
	}
}

void ARS_FPSHUD::DrawComicBook()
{
	//blue rect alpha 50%
	DrawHUDRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(1, 1, 1, 0.2333));
	DrawHUDText(VerdanaFont, "Press H", Canvas->SizeX / 2 - 40, Canvas->SizeY / 2 + 10, LC_Black, DefaultFontScale, true, FLinearColor(1, 1, 1, 0.2333));
}

int32 ARS_FPSHUD::CheckCursorInButton(const TArray<FRS_FPSHUDButtonStruct>& ButtonArray)
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
			ActiveButton_Tip = CurCheckButton->Tooltip;

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

//Check Notebook
void ARS_FPSHUD::CheckCursorInButtonsNotebook()
{
	ClickedButtonType = CheckCursorInButton(ButtonsNotebook);

	if (ClickedButtonType == BUTTONTYPE_NOTEBOOK_2)
	{
		ConfirmNotebookOpen = false;
		ButtonsNotebook.Empty();
		return;
	}
}

//Check Confirm
void ARS_FPSHUD::CheckCursorInButtonsConfirm()
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
void ARS_FPSHUD::CheckCursorInButtonsMain()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsMain);

	if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
	{
		ThePC->ConsoleCommand("RestartLevel");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_NOTEBOOK)
	{
		ConfirmNotebookOpen = true;
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	{
		ConfirmDialogOpen = true;
		return;
	}
}

void ARS_FPSHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		//Take Focus Away From All Other buttons
		return;
		//~
	}
	if (ConfirmNotebookOpen)
	{
		CheckCursorInButtonsNotebook();
		return;
	}

	//Main
	CheckCursorInButtonsMain();
}

void ARS_FPSHUD::DrawToolTip()
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
		FLinearColor(0, 0, 0, 0.332) //alpha 0.7
		);

	//Tool Tip
	DrawText(
		ActiveButton_Tip,
		LC_Black,
		xStart + 32, yStart + 20,
		UE4Font,
		DefaultFontScale * 2,
		false		//scale position of message with HUD scale
		);
}

void ARS_FPSHUD::DrawHUD_DrawCursor()
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

void ARS_FPSHUD::PlayerInputChecks()
{

	if (ThePC->WasInputKeyJustPressed(EKeys::Escape))
	{
		SetCursorMoveOnly(false);
		return;
	}
	if (ThePC->WasInputKeyJustPressed(EKeys::H))
	{
		if (InComic) {
			InComic = false;
		}

		//DontDrawMenu = !DontDrawMenu;
		DontDrawHUD = !DontDrawHUD;
		SetCursorMoveOnly(!ThePC->IsLookInputIgnored());
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



void ARS_FPSHUD::DrawHUD_Reset()
{
	ActiveButton_Type = -1;
	ActiveButton_Tip = "";
	CursorHoveringInButton = false;
}

void ARS_FPSHUD::DrawHUD()
{
	Super::DrawHUD();
	PlayerInputChecks();

	if (InComic)
	{
		DrawHUD_Reset();
		DrawComicBook();
	}
	else if (DontDrawHUD)
	{

		//No Canvas?
		if (!Canvas) return;

		//Reset States
		DrawHUD_Reset();

		// get new mouselocation
		ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);

		//Cursor In Buttons
		DrawHUD_CheckCursorInButtons();

		//Draw Dialogs
		DrawHUD_DrawDialogs();

		//Draw Cursor
		DrawHUD_DrawCursor();

	}
	else 
	{

		//Draw HUD
		//if (DontDrawHUD) return;
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
}

