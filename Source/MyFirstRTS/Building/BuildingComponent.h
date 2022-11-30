// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	float HealthCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	FVector HealthBarLocalPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Health")
	FVector2D HealthBarSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Attack")
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Attack")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FVector BuildingCenter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	float BuildingSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	float VisionRange;

public:	
	// Sets default values for this component's properties
	UBuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
