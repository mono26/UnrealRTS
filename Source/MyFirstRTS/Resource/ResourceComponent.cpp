// Copyright: For learning purposes, Mono Zubiria.


#include "ResourceComponent.h"
#include "../Component/InteractableComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UInteractableComponent* interactableComponent = this->GetOwner()->FindComponentByClass<UInteractableComponent>();
	//interactableComponent->SetInteractableRadius(this->BuildingSize);
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UResourceComponent::CanGather()
{
	return this->MineCount > 0;
}

FResource UResourceComponent::GetGatheredResource()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GetGatheredResource."));

	FResource resource = FResource(this->ResourceType, this->AmountToGive);

	this->MineCount--;

	return resource;
}

