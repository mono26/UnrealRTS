// Copyright: For learning purposes, Mono Zubiria.


#include "UnitRangedAttackComponent.h"

void UUnitRangedAttackComponent::ExecuteAttack()
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
    // Set the projectile's initial trajectory.
    FVector LaunchDirection = this->Muzzle->GetComponentRotation().Vector();
    projectile->FireInDirection(LaunchDirection);
}

void UUnitRangedAttackComponent::OnExecuteAttack()
{
}
