

#include "RomaStoria.h"
#include "MyFPSGameMode.h"
#include "MyFPSHUD.h"


AMyFPSGameMode::AMyFPSGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_MyFPSCharacter.BP_MyFPSCharacter'"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> TheHUDOb(TEXT("Blueprint'/Game/Blueprints/BP_HUD'"));
	if (TheHUDOb.Object != NULL)
	{
		HUDClass = (UClass*)TheHUDOb.Object->GeneratedClass;
	}
}

void AMyFPSGameMode::StartPlay()
{
	Super::StartPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Veni, Lusi, Dixi"));
	}
}