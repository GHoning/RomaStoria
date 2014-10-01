

#pragma once

#include "PickUp.h"
#include "ItemPickUp.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API AItemPickUp : public APickUp
{
	GENERATED_UCLASS_BODY()

	/* This Overrides the on interaction funcition*/
	void OnInteraction_Implementation() override;
	
};