// Copyright: For learning purposes, Mono Zubiria.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnWave()
{
	int spawnCount = FMath::RandRange(this->MinSpawnPerWave, this->MaxSpawnPerWave);
	for (int i = 0; i < spawnCount; i++) {
		AActor* spawnedEnemy = this->SpawnEnemy(this->GetSpawnPosition());

		if (this->OnSpawnEnemy.IsBound()) {
			this->OnSpawnEnemy.Broadcast(spawnedEnemy);
		}
	}
}

