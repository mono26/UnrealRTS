// Copyright: For learning purposes, Mono Zubiria.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UHealthComponent::GetHealthCurrent() const
{
	return this->HealthCurrent;
}

int UHealthComponent::GetMaxHealth() const
{
	return this->HealthMax;
}

void UHealthComponent::InitializeHealthValues(int HealthValue)
{
	this->HealthCurrent = this->HealthMax = HealthValue;

	this->UpdateHealthBar();
}

void UHealthComponent::OnDamage(int DamageTaken)
{
	int currentHealth = this->HealthCurrent;
	currentHealth -= DamageTaken;
	currentHealth = FMath::Max(currentHealth, 0.0f);

	this->HealthCurrent = currentHealth;

	if (this->HealthCurrent <= 0 && this->OnHealthZero.IsBound()) {
		UE_LOG(LogTemp, Warning, TEXT("OnHealthZero."));
		this->OnHealthZero.Broadcast();
	}
}

