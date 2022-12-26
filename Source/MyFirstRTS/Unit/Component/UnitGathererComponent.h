// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../RTSUnit.h"
#include "../../Resource/ResourceComponent.h"
#include "UnitGathererComponent.generated.h"

struct FGatherRequest
{
private:
	AActor* ResourceRef;

	FActionSignature OnSuccess;
	FActionSignature OnFail;

public:
	FGatherRequest() : FGatherRequest(nullptr, FActionSignature(), FActionSignature())
	{

	}

	FGatherRequest(AActor* Resource, FActionSignature OnSuccessCallback, FActionSignature OnFailCallback)
	{
		this->ResourceRef = Resource;

		this->OnSuccess = OnSuccessCallback;
		this->OnFail = OnFailCallback;
	}

	AActor* GetResourceRef() const
	{
		return this->ResourceRef;
	}

	FActionSignature GetOnSuccess() const
	{
		return this->OnSuccess;
	}

	FActionSignature GetOnFail() const
	{
		return this->OnFail;
	}

	void SetResourceRef(AActor* Resource)
	{
		this->ResourceRef = Resource;
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UUnitGathererComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Worker|Gathering")
	FResource CarriedResource;

private:
	FGatherRequest* GatherRequest;
	FExtendedTimer* GatherTimer;
	FActionSignature OnExtractResourceDelegate;

public:	
	// Sets default values for this component's properties
	UUnitGathererComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ClearGatherRequest();

	UFUNCTION(BlueprintCallable, Category = "Worker|Gathering")
	AActor* GetTargetResource() const;

	void ExtractResource();

	UFUNCTION()
	void OnExtractResource();

	void SetGatherRequest(FGatherRequest Request);

	void StoreResource();
};
