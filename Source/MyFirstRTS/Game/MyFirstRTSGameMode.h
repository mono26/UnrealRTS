// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFirstRTSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTRTS_API AMyFirstRTSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "RTSGameMode")
	TArray<AActor*> PlayerTownHalls;

public:
	UFUNCTION(BlueprintCallable, Category = "RTSGameMode")
	AActor* GetPlayerTownhall();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void FindExistingPlayerTownhalls();
};
