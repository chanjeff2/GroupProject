#include "Nerd.h"

Nerd::Nerd(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Nerd)
{
    damagePerHit = 1;
    hitPerSec = 1.0;
    effectiveTowards = set<EnemyType>{ EnemyType::CompLab , EnemyType::Desmond , EnemyType::PA };
    weakTowards = set<EnemyType>{ EnemyType::GroupProj };
    cost = 1;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
}
