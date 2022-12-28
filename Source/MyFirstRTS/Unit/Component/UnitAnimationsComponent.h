// Copyright: For learning purposes, Mono Zubiria.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnitComponent.h"
#include "UnitAnimationsComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFIRSTRTS_API UUnitAnimationsComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UUnitComponent::FOnStateChangedSignature* OnStateChangedDelegate;

	USkeletalMeshComponent* SkeletalMeshComponent;
	UUnitComponent* UnitComponent;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animations")
	UAnimationAsset* MovingAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animations")
	UAnimationAsset* AttackingAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animations")
	UAnimationAsset* GatheringAnimation;
	UPROPERTY(EditDefaultsOnly, Category = "Unit|Animations")
	UAnimationAsset* IdleAnimation;

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
	UFUNCTION(BlueprintCallable, Category = "Unit|Animations")
	void OnUnitStateChange();
};
