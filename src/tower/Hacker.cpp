#include "Hacker.h"

Hacker::Hacker(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Hacker)
{
    damagePerHit = 1;
    hitPerSec = 1.0;
    effectiveTowards = set<EnemyType>{ EnemyType::EncryptedHW , EnemyType::CompLab , EnemyType::PA };
    weakTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA };
    cost = 2;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
};
