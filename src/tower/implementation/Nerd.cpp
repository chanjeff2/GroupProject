#include "Nerd.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Nerd::Nerd(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Nerd)
{
    damagePerHit = 8;
    hitPerSec = 2.2;
    effectiveTowards = set<EnemyType>{ EnemyType::GroupProj };
    weakTowards = set<EnemyType>{};
    cost = TOWER_PRICES[5];
    range = TOWER_RANGES[5];
    attackStrategy = new NormalAttack(this);
    attackStrategy->setMaxNumOfTarget(5);
    attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[5]);

	trigger();
}
