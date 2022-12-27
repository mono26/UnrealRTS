// Copyright: For learning purposes, Mono Zubiria.


#include "WeaponSocketComponent.h"

// Sets default values for this component's properties
UWeaponSocketComponent::UWeaponSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UWeaponSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UWeaponSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}