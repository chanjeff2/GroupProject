#include "Regular.h"
#include "src/utility/GameValues.h"
<<<<<<< HEAD:src/tower/Regular.cpp
#include "attack/NormalAttack.h"
#include "aura/AuraEffect.h"

Regular::Regular(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Regular) {
	damagePerHit = 1;
=======
#include "src/tower/aura/AuraEffect.h"
#include "src/tower/attack/NormalAttack.h"

Regular::Regular(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Regular)
{
    damagePerHit = 16;
>>>>>>> dev:src/tower/implementation/Regular.cpp
	hitPerSec = 1.0;
	effectiveTowards = set<EnemyType>{};
	weakTowards = set<EnemyType>{};
    cost = TOWER_PRICES[0];
    range = 3;
	attackStrategy = new NormalAttack(this);
	attackStrategy->setMaxNumOfTarget(1);
	attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
	auraEffect = new AuraEffect(this, AuraType::Null);
}
