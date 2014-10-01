

#include "RomaStoria.h"
#include "NotePickUp.h"


ANotePickUp::ANotePickUp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void ANotePickUp::OnInteraction_Implementation() {
	//call the parent implementation of PickUp first
	Super::OnInteraction_Implementation();
}
