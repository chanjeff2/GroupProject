#include "Arts.h"

Arts::Arts(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Arts) {
    damagePerHit = 1;
    hitPerSec = 1.0;
    effectiveTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA };
    weakTowards = set<EnemyType>{ EnemyType::CompLab , EnemyType::Desmond , EnemyType::PA };
    cost = 1;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
}
