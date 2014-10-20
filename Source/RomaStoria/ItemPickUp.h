

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

	/* The Icon used in to display the item in HUD */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
		UTexture2D* ItemIcon;

	/* This Overrides the on interaction funcition*/
	void OnInteraction_Implementation() override;
	
};