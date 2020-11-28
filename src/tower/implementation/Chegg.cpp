#include "Chegg.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Chegg::Chegg(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Chegg)
{
    damagePerHit = 288;
    hitPerSec = 0.1;
    effectiveTowards = set<EnemyType>{};
    weakTowards = set<EnemyType>{ EnemyType::Midterm, EnemyType::Desmond, EnemyType::MATHExam,
                                  EnemyType::Final, EnemyType::ELPA, EnemyType::FYP };
    cost = TOWER_PRICES[7];
    range = 5;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
};
