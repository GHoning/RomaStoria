

#include "RomaStoria.h"
#include "ItemPickUp.h"


AItemPickUp::AItemPickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}


void AItemPickUp::OnInteraction_Implementation() {
	//call the parent implementation of PickUp first
	Super::OnInteraction_Implementation();
	Destroy();
}