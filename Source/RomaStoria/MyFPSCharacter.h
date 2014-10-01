

#pragma once

#include "ItemPickUp.h"
#include "GameFramework/Character.h"
#include "MyFPSCharacter.generated.h"


/**
 * 
 */
UCLASS()
class ROMASTORIA_API AMyFPSCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
	virtual void BeginPlay() override;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/* Collision Sphere*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
		TSubobjectPtr<class USphereComponent> CollisionSphere;

	/* Inventory of the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
		TArray<AItemPickUp*> Inventory;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	/* handles moving forward/backward*/
	UFUNCTION()
		void MoveForward(float Value);
	/* handles strafing */
	UFUNCTION()
		void MoveRight(float Value);
	/* sets jump flag when key is pressed*/
	UFUNCTION()
		void OnStartJump();
	/* clears jump flag when key is released */
	UFUNCTION()
		void OnStopJump();
	/* handles firing */
	UFUNCTION()
		void OnFire();
	/* handles interaction with other actors */
	UFUNCTION()
		void OnInteract();
	/* handles the storing of items */
	UFUNCTION()
		void OnPickUpItem(AItemPickUp* ItemPickUp);
	

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;

	/** Spell Offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector SpellOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AMyFPSProjectile> ProjectileClass;
};
