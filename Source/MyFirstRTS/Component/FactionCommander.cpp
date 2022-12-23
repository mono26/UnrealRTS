// Copyright: For learning purposes, Mono Zubiria.


#include "FactionCommander.h"
#include "../Game/MyFirstRTSGameMode.h"

// Sets default values for this component's properties
UFactionCommander::UFactionCommander()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	this->CommandComponent = nullptr;
}

// Called when the game starts
void UFactionCommander::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->CommandComponent = this->GetOwner()->FindComponentByClass<UCommanderComponent>();
}

// Called every frame
void UFactionCommander::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UFactionCommander::GetPlayerTownhall()
{
	UWorld* world = this->GetWorld();
	AGameModeBase* gameMode = world->GetAuthGameMode();
	AMyFirstRTSGameMode* rtsMode = Cast<AMyFirstRTSGameMode>(gameMode);
	if (rtsMode == nullptr) {
		return nullptr;
	}

	return rtsMode->GetPlayerTownhall();
}