

#pragma once

#include "InteractableActor.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API ADoor : public AInteractableActor
{
	GENERATED_UCLASS_BODY()

	/* This Overrides the on interaction funcition*/
	void OnInteraction_Implementation() override;
};
