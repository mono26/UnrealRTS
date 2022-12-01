// Copyright: For learning purposes, Mono Zubiria.


#include "BuildingComponent.h"
#include "../Component/InteractableComponent.h"
#include "../Component/HealthComponent.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UInteractableComponent* interactableComponent = this->GetOwner()->FindComponentByClass<UInteractableComponent>();
	interactableComponent->SetInteractableRadius(this->BuildingSize);

	UHealthComponent* healthComponent = this->GetOwner()->FindComponentByClass<UHealthComponent>();
	healthComponent->InitializeHealthValues(this->HealthMax);
}


// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

