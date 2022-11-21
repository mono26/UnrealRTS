// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Delegates/Delegate.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Resource/ResourceComponent.h"
#include "../Unit/UnitComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "WorkerUnit.generated.h"

UCLASS()
class MYFIRSTRTS_API AWorkerUnit : public ACharacter
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE(FOnMovementUpdateSignature);
	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FTargetChangedSignature, AWorkerUnit, OnTargetChanged, const AActor*, OldTarget, const AActor*, NewTarget);

	struct FMovementRequest
	{
		uint32 requestId;
		FOnMovementUpdateSignature OnSuccess;
		FOnMovementUpdateSignature OnFail;

		FMovementRequest(int requestId, FOnMovementUpdateSignature OnSuccess, FOnMovementUpdateSignature OnFail) {
			this->requestId = requestId;
			this->OnSuccess = OnSuccess;
			this->OnFail = OnFail;
		}
	};

public:

	UPROPERTY(BlueprintAssignable, Category = "Worker")
	FTargetChangedSignature OnTargetChanged;

private:
	UUnitComponent* UnitComponent;

	AActor* AttackTargetRef = nullptr;

	TMap<uint32, FMovementRequest> MovementRequest;

	uint32 CarriedResourceAmount;
	EResourceType CarriedResource;
	FTimerHandle GatherTimerHandle;

public:
	// Sets default values for this character's properties
	AWorkerUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	AActor* GetAttackTarget();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	void SetAttackTarget(AActor* TargetRef);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToPosition(FVector Position, FOnMovementUpdateSignature OnSuccess, FOnMovementUpdateSignature OnFail);

	UFUNCTION(BlueprintCallable, Category = "Worker|Movement")
	void MoveToActor(AActor* ActorRef, FOnMovementUpdateSignature OnSuccess, FOnMovementUpdateSignature OnFail);

	void OnMoveRequestCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStartMovement();

	//void ExtractResource(AActor* ResourceRef);

	//UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	//void OnResourceReached(AActor* ResourceRef);

	UFUNCTION(BlueprintCallable, Category = "Worker|Commands")
	void ExecuteCommand(UUnitCommand* Command);

	UFUNCTION(BlueprintCallable, Category = "Worker")
	void StopAllActions();

	UFUNCTION(BlueprintImplementableEvent, Category = "Worker|Movement")
	void OnStopAll();
};
