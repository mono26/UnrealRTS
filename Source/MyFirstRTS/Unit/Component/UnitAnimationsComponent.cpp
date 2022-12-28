// Copyright: For learning purposes, Mono Zubiria.


#include "UnitAnimationsComponent.h"

// Sets default values for this component's properties
UUnitAnimationsComponent::UUnitAnimationsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UUnitAnimationsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->SkeletalMeshComponent = this->GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	this->UnitComponent = this->GetOwner()->FindComponentByClass<UUnitComponent>();
}

// Called every frame
void UUnitAnimationsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitAnimationsComponent::OnUnitStateChange()
{
	EUnitStates currentState = this->UnitComponent->GetCurrentState();
	switch (currentState) {
		case EUnitStates::Idle: {
			this->SkeletalMeshComponent->PlayAnimation(this->IdleAnimation, true);
			break;
		}
		case EUnitStates::Moving: {
			this->SkeletalMeshComponent->PlayAnimation(this->MovingAnimation, true);
			break;
		}
		case EUnitStates::Gathering: {
			this->SkeletalMeshComponent->PlayAnimation(this->GatheringAnimation, true);
			break;
		}
		case EUnitStates::Attacking: {
			this->SkeletalMeshComponent->PlayAnimation(this->AttackingAnimation, true);
			break;
		}
		default: break;
	}
}