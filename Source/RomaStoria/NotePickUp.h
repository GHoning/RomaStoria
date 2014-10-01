

#pragma once

#include "PickUp.h"
#include "NotePickUp.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API ANotePickUp : public APickUp
{
	GENERATED_UCLASS_BODY()

	/* This Overrides the on interaction funcition*/
	void OnInteraction_Implementation() override;
	
};
