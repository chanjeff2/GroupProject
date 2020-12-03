#include "Chegg.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Chegg::Chegg(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Chegg)
{
    damagePerHit = 256;
    hitPerSec = 0.16;
    effectiveTowards = set<EnemyType>{};
    weakTowards = set<EnemyType>{ EnemyType::Midterm, EnemyType::Desmond, EnemyType::MATHExam,
                                  EnemyType::Final, EnemyType::ELPA, EnemyType::FYP };
    cost = TOWER_PRICES[7];
    range = TOWER_RANGES[7];
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[7]);

	trigger();
};
