#include "WolframAlpha.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

WolframAlpha::WolframAlpha(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::WolframAlpha)
{
    damagePerHit = 42;
    hitPerSec = 1.3;
    effectiveTowards = set<EnemyType>{ EnemyType::MathHW };
    weakTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA, EnemyType::Midterm,
                                  EnemyType::MATHExam, EnemyType::FYP };
    cost = TOWER_PRICES[2];
    range = TOWER_RANGES[2];
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[2]);

	trigger();
};
