// Copyright: For learning purposes, Mono Zubiria.


#include "RTSProjectileMovementComponent.h"

// Sets default values for this component's properties
URTSProjectileMovementComponent::URTSProjectileMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTSProjectileMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URTSProjectileMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (!this->bIsMoving || this->CurrentTimer > this->TimeToReachTarget) {
		return;
	}

	FVector startingPoint = this->StartPoint;
	// startingPoint.Z = 0.0f;
	FVector endingPoint = this->EndPoint;
	// endingPoint.Z = 0.0f;

	FVector nextPosition = FMath::Lerp(startingPoint, endingPoint, this->CurrentTimer / this->TimeToReachTarget);
	FVector nextDirection = nextPosition - this->GetOwner()->GetActorLocation();

	this->CurrentTimer += DeltaTime;

	this->GetOwner()->SetActorLocation(nextPosition);
}

void URTSProjectileMovementComponent::SetStartPoint(FVector Point)
{
	this->StartPoint = Point;
}

void URTSProjectileMovementComponent::SetEndPoint(FVector Point)
{
	this->EndPoint = Point;
}

void URTSProjectileMovementComponent::StartMovement(bool StartMovement)
{
	FVector direction = this->EndPoint - this->StartPoint;
	// time = distance/velocity.
	this->TimeToReachTarget = FVector(direction.X, direction.Y, 0.0f).Length() / this->MovementSpeed;
	this->CurrentTimer = 0.0f;

	UE_LOG(LogTemp, Warning, TEXT("Time to reach target."));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(this->TimeToReachTarget));

	this->bIsMoving = StartMovement;
}
