// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../WorkerUnit.h"
#include "UnitAttackComponent.generated.h"

struct FAttackRequest
{
private:
	float DistanceToTarget;

	AActor* AttackTargetRef;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FAttackRequest() : FAttackRequest(nullptr, FActionSignature(), FActionSignature())
	{

	}

	FAttackRequest(AActor* AttackTarget, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->AttackTargetRef = AttackTarget;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetAttackTargetRef() const
	{
		return this->AttackTargetRef;
	}

	FActionSignature GetOnSuccess() const
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail() const
	{
		return this->OnFail;
	}

	float GetDistanceToTarget() const
	{
		return this->DistanceToTarget;
	}

	void SetDistanceToTarget(float Distance)
	{
		this->DistanceToTarget = Distance;
	}

	void SetAttackTargetRef(AActor* AttackTarget)
	{
		this->AttackTargetRef = AttackTarget;
	}

	void SetOnSuccess(FActionSignature OnSuccessCallback)
	{
		this->OnSuccess = OnSuccessCallback;
	}

	void SetOnFail(FActionSignature OnFailCallback)
	{
		this->OnFail = OnFailCallback;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetChangedSignature, const AActor*, OldTarget, const AActor*, NewTarget);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UUnitAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Worker|Target")
	FTargetChangedSignature OnTargetChangedEvent;

private:
	FAttackRequest* AttackRequest;
	FExtendedTimer* AttackTimer;
	FActionSignature OnExecuteAttackDelegate;

public:	
	// Sets default values for this component's properties
	UUnitAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void ExecuteAttack();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	void ClearAttackRequest();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	AActor* GetAttackTarget() const;

	void SetAttackRequest(FAttackRequest Request);

	UFUNCTION()
	virtual void OnExecuteAttack();
};
