// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../RTSUnit.h"
#include "../Command/UnitCommand.h"
#include "UnitComponentInterface.h"
#include "UnitAttackComponent.generated.h"

struct FAttackRequest
{
private:
	float DistanceToTarget;

	AActor* AttackTarget;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FAttackRequest() : FAttackRequest(nullptr, FActionSignature(), FActionSignature())
	{

	}

	FAttackRequest(AActor* Target, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->AttackTarget = Target;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetAttackTarget() const
	{
		return this->AttackTarget;
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

	void SetAttackTarget(AActor* Target)
	{
		this->AttackTarget = Target;
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
class MYFIRSTRTS_API UUnitAttackComponent : public UActorComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Worker|Target")
	FTargetChangedSignature OnTargetChangedEvent;

protected:
	FExtendedTimer* AttackTimer;

	FAttackRequest* AttackRequest;
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

protected:
	UFUNCTION()
	virtual void OnExecuteAttack();

public:
	virtual void ExecuteAttack();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	void ClearAttackRequest();

	UFUNCTION(BlueprintCallable, Category = "Worker|Attack")
	AActor* GetAttackTarget() const;

	void SetAttackRequest(FAttackRequest Request);

	void StopAction() override;
};
