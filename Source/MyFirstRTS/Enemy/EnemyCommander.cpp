// Copyright: For learning purposes, Mono Zubiria.


#include "EnemyCommander.h"
#include "EnemySpawner.h"
#include "../Player/PlayerCommander.h"
#include "../Game/MyFirstRTSGameMode.h"

void UEnemyCommander::StartSpawn()
{
	AEnemySpawner* spawner = Cast<AEnemySpawner>(this->GetOwner());
	spawner->SpawnWave();

	//spawner->GetWorld()->GetTimerManager().SetTimer(this->SpawnTimerHandle, [&]() {
	//	spawner->SpawnWave();
	//	// TODO delete this?
	//	}, this->TimeBetweenWaves, this->bInfiniteWaves);
}