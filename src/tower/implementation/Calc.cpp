#include "Calc.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Calc::Calc(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Calc)
{
    damagePerHit = 26;
    hitPerSec = 1.3;
    effectiveTowards = set<EnemyType>{ EnemyType::MathHW };
    weakTowards = set<EnemyType>{ EnemyType::MATHExam, EnemyType::Essay, EnemyType::ELPA };
    cost = TOWER_PRICES[4];
    range = TOWER_RANGES[4];
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[4]);

	trigger();
};
