#include "Hacker.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Hacker::Hacker(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Hacker)
{
    damagePerHit = 12;
    hitPerSec = 1.2;
    effectiveTowards = set<EnemyType>{ EnemyType::COMPLab , EnemyType::PA, EnemyType::PopQuiz };
    weakTowards = set<EnemyType>{ EnemyType::Essay , EnemyType::ELPA, EnemyType::EncryptedHW };
    cost = TOWER_PRICES[3];
    range = TOWER_RANGES[3];
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(1);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[3]);

	trigger();
};
