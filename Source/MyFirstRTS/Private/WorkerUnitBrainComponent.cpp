// Copyright: For learning purposes, Mono Zubiria.


#include "WorkerUnitBrainComponent.h"

// Sets default values for this component's properties
UWorkerUnitBrainComponent::UWorkerUnitBrainComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	PerceptionComponent = this->CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}


// Called when the game starts
void UWorkerUnitBrainComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWorkerUnitBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UWorkerUnitBrainComponent::GetNextTargetInSight()
{
	return nullptr;
}

AActor* UWorkerUnitBrainComponent::GetPlayerTownhall()
{
	return nullptr;
}

void UWorkerUnitBrainComponent::OnTargetChanged()
{
}

void UWorkerUnitBrainComponent::OnSightUpdated(AActor* Instigator)
{
	if (Instigator == nullptr) {
		return;
	}


}

AActor* UWorkerUnitBrainComponent::SelectClosestActor(AActor* ActorARef, AActor* ActorBRef)
{
	if (ActorARef == nullptr) {
		return ActorBRef;
	}
	else if (ActorBRef == nullptr) {
		return ActorARef;
	}
	else if (ActorARef == nullptr && ActorBRef == nullptr) {
		return nullptr;
	}

	AActor* owner = this->GetOwner();
	FVector ownerLocation = owner->GetActorLocation();

	FVector aLocation = ActorARef->GetActorLocation();
	FVector bLocation = ActorBRef->GetActorLocation();

	float distanceToA = FVector::Distance(ownerLocation, aLocation);
	float distanceToB = FVector::Distance(ownerLocation, bLocation);

	return distanceToA < distanceToB ? ActorARef : ActorBRef;
}

