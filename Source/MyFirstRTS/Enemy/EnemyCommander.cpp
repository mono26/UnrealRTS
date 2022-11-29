// Copyright: For learning purposes, Mono Zubiria.


#include "EnemyCommander.h"
#include "EnemySpawner.h"
#include "../Player/PlayerCommander.h"
#include "../Game/MyFirstRTSGameMode.h"

// Sets default values for this component's properties
UEnemyCommander::UEnemyCommander()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->CommandComponent = nullptr;
}


// Called when the game starts
void UEnemyCommander::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->CommandComponent = this->GetOwner()->FindComponentByClass<UCommanderComponent>();
}


// Called every frame
void UEnemyCommander::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UEnemyCommander::GetPlayerTownhall()
{
	UWorld* world = this->GetOwner()->GetWorld();
	AGameModeBase* gameMode = world->GetAuthGameMode();
	AMyFirstRTSGameMode* rtsMode = Cast<AMyFirstRTSGameMode>(gameMode);
	if (rtsMode == nullptr) {
		return nullptr;
	}

	return rtsMode->GetPlayerTownhall();
}

void UEnemyCommander::StartSpawn()
{
	AEnemySpawner* spawner = Cast<AEnemySpawner>(this->GetOwner());
	spawner->SpawnWave();

	//spawner->GetWorld()->GetTimerManager().SetTimer(this->SpawnTimerHandle, [&]() {
	//	spawner->SpawnWave();
	//	// TODO delete this?
	//	}, this->TimeBetweenWaves, this->bInfiniteWaves);
}

