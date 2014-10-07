

#include "RomaStoria.h"
#include "Trigger.h"
#include "MyFPSCharacter.h"


ATrigger::ATrigger(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Create the root SphereComponent to handle the interactable collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	//set up a notification for when this component overlaps something
	//BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnBeginOverlap);
	//BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATrigger::OnOverlap);

	//set the sphere BaseCollisionComponent as the root Component
	RootComponent = BaseCollisionComponent;
}

/*void ATrigger::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool HitBool, FHitResult& Hit)
{
	AMyFPSCharacter* const Player = Cast<AMyFPSCharacter>(OtherActor);
	if (Player)
	{
		//OnOverlapByPlayer();
	}
}

void ATrigger::OnOverlapByPlayer()
{
	//OnOverlapByPlayer has no implementation.
}*/