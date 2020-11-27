#include "Chegg.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Chegg::Chegg(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Chegg)
{
    damagePerHit = 1;
    hitPerSec = 1.0;
    effectiveTowards = set<EnemyType>{ EnemyType::NormalHW , EnemyType::MathHW };
    weakTowards = set<EnemyType>{ EnemyType::PopQuiz };
    cost = 2;
    range = 2;
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, AuraType::Null);
};
