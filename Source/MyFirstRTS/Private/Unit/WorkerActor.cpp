// Copyright: For learning purposes, Mono Zubiria.


#include "Unit/WorkerActor.h"

// Sets default values
AWorkerActor::AWorkerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorkerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorkerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

