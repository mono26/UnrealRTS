// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Component/CommanderComponent.h"
#include "FactionCommander.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UFactionCommander : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TArray<AActor*> ActiveUnits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FactionCommander|Component")
	UCommanderComponent* CommandComponent = nullptr;

public:	
	// Sets default values for this component's properties
	UFactionCommander();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerCommander")
	AActor* GetPlayerTownhall();
};
