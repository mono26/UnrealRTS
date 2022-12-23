// Copyright: For learning purposes, Mono Zubiria.


#include "PlayerCommander.h"
#include "../Game/MyFirstRTSGameMode.h"

// Sets default values for this component's properties
APlayerCommander::APlayerCommander() : Super()
{

}

// Called when the game starts
void APlayerCommander::BeginPlay()
{
	Super::BeginPlay();

	// ...
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
