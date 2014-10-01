

#include "RomaStoria.h"
#include "PickUp.h"


APickUp::APickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APickUp::OnInteraction_Implementation() {
	//call the parent implementation of InteractableActor first
	Super::OnInteraction_Implementation();

	//REMOVE when testing is done
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Destory PickUp"));
	}

	// Destroy the item (remove from world/level)
	Destroy();
}


