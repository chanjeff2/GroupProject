#include "Regular.h"
#include "src/utility/GameValues.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Regular::Regular(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Regular)
{
    damagePerHit = 16;
	hitPerSec = 1.0;
	effectiveTowards = set<EnemyType>{};
	weakTowards = set<EnemyType>{};
    cost = TOWER_PRICES[0];
    range = TOWER_RANGES[0];
	attackStrategy = new NormalAttack(this);
	attackStrategy->setMaxNumOfTarget(1);
	attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
    auraEffect = new AuraEffect(this, TOWER_AURAS[0]);

	trigger();
}
