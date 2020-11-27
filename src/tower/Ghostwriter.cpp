#include "Ghostwriter.h"

Ghostwriter::Ghostwriter(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Ghostwriter)
{
    damagePerHit = 1;
    hitPerSec = 1.0;
    effectiveTowards = set<EnemyType>{ EnemyType::Essay };
    weakTowards = set<EnemyType>{ EnemyType::Midterm , EnemyType::Final };
    cost = 2;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
};
