

#pragma once

#include "InteractableActor.h"
#include "PickUp.generated.h"

/**
 * A class used for items that needs to be removed after the player has interacted with it.
 */
UCLASS()
class ROMASTORIA_API APickUp : public AInteractableActor
{
	GENERATED_UCLASS_BODY()

	/* This Overrides the on interaction funcition*/
	void OnInteraction_Implementation() override;
	
};
