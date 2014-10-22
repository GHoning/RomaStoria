

#include "RomaStoria.h"
#include "MyFPSCharacter.h"
#include "MyFPSProjectile.h"
#include "RS_FPSHUD.h"
#include "ItemPickUp.h"
#include "NotePickUp.h"
#include "Engine/Canvas.h"


AMyFPSCharacter::AMyFPSCharacter(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	// Create a CameraComponent
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;

	// Position the camera a bit above the eyes
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FirstPersonMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true); // only the owning player will see this mesh
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	// everyone but the owner can see the regular body mesh
	Mesh->SetOwnerNoSee(true);

	// Create a CollisionMesh
	CollisionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionSphere"));
	CollisionSphere->AttachTo(FirstPersonCameraComponent);
	CollisionSphere->SetSphereRadius(200.f);
}

void AMyFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("MyFPSCharacter Initialized"));
	}
}

void AMyFPSCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyFPSCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyFPSCharacter::OnStopJump);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyFPSCharacter::OnFire);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyFPSCharacter::OnInteract);
	InputComponent->BindAction("DropItem", IE_Pressed, this, &AMyFPSCharacter::OnDropItem);

	InputComponent->BindAxis("MoveForward", this, &AMyFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyFPSCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMyFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyFPSCharacter::AddControllerPitchInput);
}

void AMyFPSCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyFPSCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyFPSCharacter::OnStartJump()
{
	bPressedJump = true;
}

void AMyFPSCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AMyFPSCharacter::OnFire()
{
	// try and find a projectile
	if (ProjectileClass != NULL)
	{
		// get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// SpellOffset is in camera space, so transform it to worldspace before offsetting from the camera to find the final spell position
		FVector const SpellLocation = CameraLoc + FTransform(CameraRot).TransformVector(SpellOffset);
		FRotator SpellRotation = CameraRot;
		SpellRotation.Pitch += 10.0f; // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the spell location
			AMyFPSProjectile* const Projectile = World->SpawnActor<AMyFPSProjectile>(ProjectileClass, SpellLocation, SpellRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = SpellRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}

void AMyFPSCharacter::OnInteract()
{

	// get all overlapping Actors
	TArray<AActor*>OverlappingActors;

	// get a raycast to the object and then cast for items whitin the collision sphere
	// get the camera location and rotation
	FVector CameraLoc;
	FRotator CameraRot;
	GetActorEyesViewPoint(CameraLoc, CameraRot);

	// set up the variables
	const FVector Start = CameraLoc;
	const FVector End = Start + GetControlRotation().Vector() * 256;

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	FHitResult RV_Hit(ForceInit);

	GetWorld()->LineTraceSingle(RV_Hit, Start, End, ECC_Pawn, RV_TraceParams);

	if (RV_Hit.GetActor() != NULL) {
		CollisionSphere->GetOverlappingActors(OverlappingActors);

		// for each overlapping actor
		for (int32 iOverlapping = 0; iOverlapping < OverlappingActors.Num(); ++iOverlapping)
		{
			// cast the collected actor to ItemPickUp and NotePickUp
			AItemPickUp* const ItemPickUp = Cast<AItemPickUp>(OverlappingActors[iOverlapping]);
			ANotePickUp* const NotePickUp = Cast<ANotePickUp>(OverlappingActors[iOverlapping]);

			if (ItemPickUp) {
				// REMOVE when testing is done
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I found an ItemPickUp."));
				}

				OnPickUpItem(ItemPickUp);
				ItemPickUp->OnInteraction();
			}

			if (NotePickUp) {
				// REMOVE when testing is done
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I found an NotePickUp."));
				}
				OnPickUpNote(NotePickUp);
				NotePickUp->OnInteraction();
			}
		}
	}


}

void AMyFPSCharacter::OnPickUpItem(AItemPickUp* ItemPickUp)
{
	Inventory.Add(ItemPickUp);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I Stored the ItemPickUp in my Inventory."));
	}

}

void AMyFPSCharacter::OnPickUpNote(ANotePickUp* NotePickUp)
{
	Notebook.Add(NotePickUp);

	// REMOVE when testing is done
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I stored the NotePickUp in my Notebook."));
	}
}

void AMyFPSCharacter::OnDropItem()
{
	if (Inventory.Num() > 0)
	{
		// get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// SpellOffset is in camera space, so transform it to worldspace before offsetting from the camera to find the final spell position
		FVector const ItemLocation = CameraLoc + FTransform(CameraRot).TransformVector(SpellOffset);
		FRotator ItemRotation = CameraRot;
		ItemRotation.Pitch += 10.0f; // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the spell location
			AItemPickUp* const DropItem = World->SpawnActor<AItemPickUp>(PickUpItemClass, ItemLocation, ItemRotation, SpawnParams);
		}

		Inventory.RemoveAt(0);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I dropped the ItemPickUp in my Inventory."));
		}
	}
}