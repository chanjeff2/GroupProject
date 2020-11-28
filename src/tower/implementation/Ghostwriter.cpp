#include "Ghostwriter.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Ghostwriter::Ghostwriter(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Ghostwriter)
{
    damagePerHit = 32;
    hitPerSec = 0.4;
    effectiveTowards = set<EnemyType>{ EnemyType::Essay, EnemyType::Midterm, EnemyType::MATHExam };
    weakTowards = set<EnemyType>{ EnemyType::Final, EnemyType::FYP };
    cost = TOWER_PRICES[6];
    range = 9;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::RageAura);
};
