

#pragma once

#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

/**
 *	Trigger is an object that does something* when the player overlaps it. *This is determined in a blueprint.
 */
UCLASS()
class ROMASTORIA_API ATrigger : public AActor
{
	GENERATED_UCLASS_BODY()
	/*simple collision primitive to use as root component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/* Function to call when something overlaps the object */
	/*UFUNCTION(BlueprintNativeEvent, Category = Trigger)
		void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool HitBool, const FHitResult& Hit);*/

	/* Function to call when a player overlaps the object */
	/*UFUNCTION(BlueprintNativeEvent, Category = Trigger)
		void OnOverlapByPlayer();*/
};
