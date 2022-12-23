// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Unit/Command/UnitCommand.h"
#include "../Resource/ResourceComponent.h"
#include "../Component/CommanderComponent.h"
#include "PlayerCommander.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API APlayerCommander : public APlayerController
{
	GENERATED_BODY()
	
private:
	TMap<EResourceType, int> StoredResources;

public:
	APlayerCommander();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerCommander|Resources")
	TMap<EResourceType, int> GetStoredResources() const;

	void ReceiveResources(EResourceType ResourceType, int ResourceAmount);

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerCommander|Resources")
	void OnReceiveResources(EResourceType ResourceType);
};
