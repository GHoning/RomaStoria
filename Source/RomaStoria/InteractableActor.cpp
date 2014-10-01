

#include "RomaStoria.h"
#include "InteractableActor.h"



AInteractableActor::AInteractableActor(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Create the root SphereComponent to handle the interactable collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	//set the sphere BaseCollisionComponent as the root Component
	RootComponent = BaseCollisionComponent;
	
	//Create the static mesh component
	InteractableMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("InteractableMesh"));

	// Turn Physics on for the static mesh
	InteractableMesh->SetSimulatePhysics(true);

	// Attach the staticMeshComponent to the rootComponent
	InteractableMesh->AttachTo(RootComponent);
}

void AInteractableActor::OnInteraction_Implementation()
{
	//There is no default behavoir for an interactable actor.
}

