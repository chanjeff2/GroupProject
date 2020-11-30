#include "Arts.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Arts::Arts(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Arts) {
    damagePerHit = 22;
    hitPerSec = 0.8;
    effectiveTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA, EnemyType::FYP };
    weakTowards = set<EnemyType>{ EnemyType::COMPLab, EnemyType::Desmond, EnemyType::PA,
                                  EnemyType::MathHW, EnemyType::MATHExam };
    cost = TOWER_PRICES[1];
    range = 3;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);

	trigger();
}
