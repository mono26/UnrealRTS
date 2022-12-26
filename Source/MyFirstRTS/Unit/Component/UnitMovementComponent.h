// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Command/UnitCommand.h"
#include "Navigation/PathFollowingComponent.h"
#include "UnitComponentInterface.h"
#include "UnitMovementComponent.generated.h"

struct FMovementRequest
{
private:
	uint32 RequestId;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FMovementRequest() : FMovementRequest(0, FActionSignature(), FActionSignature())
	{

	}

	FMovementRequest(int requestId, FActionSignature OnSuccess, FActionSignature OnFail)
	{
		this->RequestId = requestId;
		this->OnSuccess = OnSuccess;
		this->OnFail = OnFail;
	}

	uint32 GetResquestId()
	{
		return this->RequestId;
	}

	FActionSignature GetOnSuccess()
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail()
	{
		return this->OnFail;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UUnitMovementComponent : public UActorComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

private:
	TMap<uint32, FMovementRequest> MovementRequest;

public:	
	// Sets default values for this component's properties
	UUnitMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToPosition(FVector Position, FActionSignature OnSuccess, FActionSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FActionSignature OnSuccess, FActionSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	void StopAction() override;
};
