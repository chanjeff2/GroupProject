#include "Calc.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Calc::Calc(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Calc)
{
    damagePerHit = 1;
    hitPerSec = 1.0;
	effectiveTowards = set<EnemyType>{ EnemyType::MATHExam , EnemyType::MathHW };
    weakTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA };
    cost = 2;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
};
