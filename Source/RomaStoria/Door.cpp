

#include "RomaStoria.h"
#include "Door.h"


ADoor::ADoor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ADoor::OnInteraction_Implementation() {
	//call the parent implementation of InteractableActor first
	Super::OnInteraction_Implementation();

	//REMOVE when testing is done
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Destory Door"));
	}

	// Destroy the item (remove from world/level)
	Destroy();
}
