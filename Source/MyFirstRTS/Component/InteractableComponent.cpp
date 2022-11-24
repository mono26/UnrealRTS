// Copyright: For learning purposes, Mono Zubiria.


#include "InteractableComponent.h"
#include "InteractionPoint.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USceneComponent* UInteractableComponent::GetClosestInteractionPointTo(AActor* Actor)
{
	if (Actor == nullptr) {
		return nullptr;
	}

	TArray<UInteractionPoint*> points;
	this->GetOwner()->GetComponents<UInteractionPoint>(points, false);
	if (points.IsEmpty()) {
		return nullptr;
	}

	float closestSqrDistance = 9999999999999999.0f;
	UInteractionPoint* closestPoint = nullptr;
	for (UInteractionPoint* point : points) {
		if (closestPoint == nullptr) {
			closestSqrDistance = FVector::DistSquared(Actor->GetActorLocation(), point->GetComponentLocation());
			closestPoint = point;
		}

		float sqrDistance = FVector::DistSquared(Actor->GetActorLocation(), point->GetComponentLocation());
		if (sqrDistance < closestSqrDistance) {
			closestSqrDistance = sqrDistance;
			closestPoint = point;
		}
	}

	return closestPoint;
}

float UInteractableComponent::GetInteractableRadius()
{
	// Use only one component since all must be uniformly scaled.
	float scale = this->GetOwner()->GetActorScale().X;
	return this->InteractableRadius * scale;
}

void UInteractableComponent::SetInteractableRadius(float Radius)
{
	this->InteractableRadius = Radius;
}