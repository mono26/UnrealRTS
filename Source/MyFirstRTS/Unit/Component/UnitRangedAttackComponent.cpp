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
        this->AttackRequest->GetOnFail().ExecuteIfBound();
        return;
    }

    ARTSUnit* asWorker = Cast<ARTSUnit>(this->GetOwner());

    UInteractableComponent* interactableComponent = this->GetAttackTarget()->FindComponentByClass<UInteractableComponent>();

    if (asWorker == nullptr || interactableComponent == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("There's something wrong with the unit."));
        this->AttackRequest->GetOnFail().ExecuteIfBound();
        return;
    }

    this->AttackRequest->SetDistanceToTarget(FVector::DistSquared(this->GetOwner()->GetActorLocation(), interactableComponent->GetClosestInteractionPositionTo(this->GetOwner())));

    float swingDuration = asWorker->GetUnitComponent()->AttackSwingDuration;

    UWorld* world = this->GetWorld();
    this->AttackTimer = new FExtendedTimer(&world->GetTimerManager(), swingDuration, this->OnExecuteAttackDelegate, this->AttackRequest->GetOnFail());

    asWorker->GetUnitComponent()->SetCurrentState(EUnitStates::Attacking);
}

void UUnitRangedAttackComponent::OnExecuteAttack()
{
    if (this->Muzzle == nullptr) {
        this->AttackRequest->GetOnFail().ExecuteIfBound();
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("OnExecuteAttack."));

    ARTSProjectile* projectile = this->CreateProjectile();

    if (projectile == nullptr) {
        this->AttackRequest->GetOnFail().ExecuteIfBound();
        return;
    }

    projectile->FireProjectile(this->Muzzle->GetComponentLocation(), this->GetAttackTarget()->GetTargetLocation());

    this->AttackRequest->GetOnSuccess().ExecuteIfBound();
}

ARTSProjectile* UUnitRangedAttackComponent::CreateProjectile()
{
    // Attempt to create a projectile.
    if (this->ProjectileClass == nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("No projectile class assigned."));
        return nullptr;
    }

    UWorld* world = this->GetWorld();
    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this->GetOwner();
    spawnParams.Instigator = this->GetOwner()->GetInstigator();

    // Spawn the projectile at the muzzle.
    ARTSProjectile* projectile = world->SpawnActor<ARTSProjectile>(this->ProjectileClass, this->Muzzle->GetComponentLocation(), this->Muzzle->GetComponentRotation(), spawnParams);
    projectile->SetProjectileCreator(this->GetOwner());
    projectile->SetOnImpact(this->OnImpactDelegate);

    return projectile;
}

void UUnitRangedAttackComponent::OnImpact(ARTSProjectile* Projectile)
{
    AActor* target = this->GetAttackTarget();
    if (target == nullptr) {
        return;
    }

    ARTSUnit* asUnit = Cast<ARTSUnit>(this->GetOwner());

    TArray<AActor*> targets { target };
    Projectile->DealDamage(asUnit->GetUnitComponent()->AttackDamage, targets);
}
