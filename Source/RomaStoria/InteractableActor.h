

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

/**
*	Interactable Actor is the base of all intreractable objects in our game
*/

UCLASS()
class ROMASTORIA_API AInteractableActor : public AActor
{
	GENERATED_UCLASS_BODY()

	/*simple collision primitive to use as root component  */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Interactable)
		TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/* StaticMeshComponent to represent the interactable object in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Interactable)
		TSubobjectPtr<UStaticMeshComponent> InteractableMesh;

	/* Function to call when the object is interacted with */
	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
		void OnInteraction();
	
};
