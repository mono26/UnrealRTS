// Copyright: For learning purposes, Mono Zubiria.


#include "UnitRangedAttackComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../RTSUnit.h"
#include "../../Component/InteractableComponent.h"

UUnitRangedAttackComponent::UUnitRangedAttackComponent() : Super()
{
    this->OnImpactDelegate.BindUFunction(this, FName("OnImpact"));
}

// Called when the game starts
void UUnitRangedAttackComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
    this->Muzzle = this->GetOwner()->FindComponentByClass<UWeaponSocketComponent>();
}

void UUnitRangedAttackComponent::ExecuteAttack()
{
    if (this->GetAttackTarget() == nullptr) {
        return;
    }

    ARTSUnit* asWorker = Cast<ARTSUnit>(this->GetOwner());

    UInteractableComponent* interactableComponent = this->GetAttackTarget()->FindComponentByClass<UInteractableComponent>();

    this->AttackRequest->SetDistanceToTarget(FVector::DistSquared(this->GetOwner()->GetActorLocation(), interactableComponent->GetClosestInteractionPositionTo(this->GetOwner())));

    float swingDuration = asWorker->GetUnitComponent()->AttackSwingDuration;

    UWorld* world = this->GetWorld();
    this->AttackTimer = new FExtendedTimer(&world->GetTimerManager(), swingDuration, this->OnExecuteAttackDelegate, this->AttackRequest->GetOnFail());

    asWorker->GetUnitComponent()->SetCurrentState(EUnitStates::Attacking);
}

void UUnitRangedAttackComponent::OnExecuteAttack()
{
    // Attempt to fire a projectile.
    if (!this->ProjectileClass) {
        return;
    }

    UWorld* world = this->GetWorld();
    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this->GetOwner();
    spawnParams.Instigator = this->GetOwner()->GetInstigator();

    // Spawn the projectile at the muzzle.
    ARTSProjectile* projectile = world->SpawnActor<ARTSProjectile>(this->ProjectileClass, this->Muzzle->GetComponentLocation(), this->Muzzle->GetComponentRotation(), spawnParams);
    projectile->SetOnImpact(this->OnImpactDelegate);
    // Set the projectile's initial trajectory.
    FVector launchDirection = this->GetAttackTarget()->GetTargetLocation() - this->Muzzle->GetComponentLocation();
    projectile->FireInDirection(launchDirection);
}

void UUnitRangedAttackComponent::OnImpact()
{
    AActor* target = this->GetAttackTarget();
    if (target == nullptr) {
        this->AttackRequest->GetOnFail().ExecuteIfBound();
        return;
    }

    ARTSUnit* asWorker = Cast<ARTSUnit>(this->GetOwner());

    UGameplayStatics::ApplyDamage(target, asWorker->GetUnitComponent()->AttackDamage, asWorker->GetController(), asWorker, nullptr);

    this->AttackRequest->GetOnSuccess().ExecuteIfBound();
}
