// Copyright: For learning purposes, Mono Zubiria.

#include "MyFirstRTSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Building/BuildingActor.h"

AActor* AMyFirstRTSGameMode::GetPlayerTownhall()
{
    if (this->PlayerTownHalls.IsEmpty() || this->PlayerTownHalls.Num() == 0) {
        return nullptr;
    }

    int index = FMath::RandRange(0, this->PlayerTownHalls.Num() - 1);
    return this->PlayerTownHalls[index];
}

void AMyFirstRTSGameMode::FindExistingPlayerTownhalls()
{
    UWorld* world = this->GetWorld();

    TArray<AActor*> townHalls;
    UGameplayStatics::GetAllActorsOfClass(world, ABuildingActor::StaticClass(), townHalls);
    if (townHalls.IsEmpty()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Townhalls found."));
        return;
    }

    for (AActor* townHall : townHalls) {
        if (townHall->ActorHasTag(FName("Townhall"))) {
            this->PlayerTownHalls.Add(townHall);
        }
    }
}
