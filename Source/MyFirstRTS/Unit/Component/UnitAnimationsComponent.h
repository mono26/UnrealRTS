// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnitComponent.h"
#include "UnitAnimationsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTRTS_API UUnitAnimationsComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	USkeletalMeshComponent* SkeletalMeshComponent;
	UUnitComponent* UnitComponent;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animation")
	UAnimationAsset* MovingAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animation")
	UAnimationAsset* AttackingAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animation")
	UAnimationAsset* GatherinAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animation")
	UAnimationAsset* IdelAnimation;

public:	
	// Sets default values for this component's properties
	UUnitAnimationsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void OnUnitStateChange();
};
