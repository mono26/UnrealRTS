// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Unit/Command/UnitCommand.h"
#include "ResourceComponent.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	None,
	Gold,
};

USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ResourceType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	int ResourceAmount;

public:
	FResource() : FResource(EResourceType::None, 0)
	{

	}

	FResource(EResourceType Type, int Amount)
	{
		this->ResourceType = Type;
		this->ResourceAmount = Amount;
	}
};

// TODO make this an event.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastActionSignature);

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Resource")
	FMulticastActionSignature OnResourceGatheredEvent;
	UPROPERTY(BlueprintAssignable, Category = "Resource")
	FMulticastActionSignature OnResourceDepletedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EResourceType ResourceType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int MineCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int AmountToGive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	float TimeToGatherInSeconds;

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanGather();

	FResource GetGatheredResource();
};
