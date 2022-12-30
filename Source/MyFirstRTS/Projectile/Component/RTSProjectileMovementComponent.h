// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RTSProjectileMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API URTSProjectileMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	bool bIsMoving;

	float CurrentTimer;
	float TimeToReachTarget;

	FVector StartPoint;
	FVector EndPoint;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	float ArcHeight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	float MovementSpeed;

public:	
	// Sets default values for this component's properties
	URTSProjectileMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetStartPoint(FVector Point);
	void SetEndPoint(FVector Point);

	void StartMovement(bool StartMovement);
};
