// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Unit/Command/MovementCommand.h"
#include "../Unit/Command/StopCommand.h"
#include "../Game/MyFirstRTSGameMode.h"
#include "../Unit/Command/GatherCommand.h"
#include "../Unit/Command/StoreCommand.h"

// Sets default values for this component's properties
APlayerCommander::APlayerCommander() : Super()
{
	this->CommandComponent = nullptr;
}


// Called when the game starts
void APlayerCommander::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->CommandComponent = this->FindComponentByClass<UCommanderComponent>();
}

AActor* APlayerCommander::GetPlayerTownhall()
{
	UWorld* world = this->GetWorld();
	AGameModeBase* gameMode = world->GetAuthGameMode();
	AMyFirstRTSGameMode* rtsMode = Cast<AMyFirstRTSGameMode>(gameMode);
	if (rtsMode == nullptr) {
		return nullptr;
	}

	return rtsMode->GetPlayerTownhall();
}

TMap<EResourceType, int> APlayerCommander::GetStoredResources() const
{
	return this->StoredResources;
}

void APlayerCommander::ReceiveResources(EResourceType ResourceType, int ResourceAmount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReceiveResources"));

	if (this->StoredResources.Contains(ResourceType)) {
		this->StoredResources[ResourceType] += ResourceAmount;
	}
	else {
		this->StoredResources.Add(ResourceType, ResourceAmount);
	}

	this->OnReceiveResources(ResourceType);
}
