

#pragma once

#include "GameFramework/GameMode.h"
#include "MyFPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROMASTORIA_API AMyFPSGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
	virtual void StartPlay() override;
};
