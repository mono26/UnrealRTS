// Copyright: For learning purposes, Mono Zubiria.


#include "UnitComponent.h"

// Sets default values for this component's properties
UUnitComponent::UUnitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->CurrentState = EUnitStates::None;
}


// Called when the game starts
void UUnitComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUnitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EUnitStates UUnitComponent::GetCurrentState()
{
	return this->CurrentState;
}

void UUnitComponent::SetCurrentState(EUnitStates NewState)
{
	this->CurrentState = NewState;
	if (this->OnCurrentStateChanged.IsBound()) {
		this->OnCurrentStateChanged.Broadcast();
	}
}