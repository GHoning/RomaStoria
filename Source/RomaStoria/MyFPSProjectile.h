

#pragma once

#include "GameFramework/Actor.h"
#include "MyFPSProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API AMyFPSProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	/* Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		TSubobjectPtr<USphereComponent> CollisionComp;

	/* Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	/* called when projectile hits something */
	UFUNCTION()
		void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	/* inits velocity of the projectile in the fire direction */
	void InitVelocity(const FVector& ShootDirection);
	
};
