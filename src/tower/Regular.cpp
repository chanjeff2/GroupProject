#include "Regular.h"

Regular::Regular(Cell* position, TowerUtility *towerUtility): ITower(position, towerUtility, TowerType::Regular)
{
	damagePerHit = 1;
	hitPerSec = 1.0;
	effectiveTowards = set<EnemyType>{};
	weakTowards = set<EnemyType>{};
	cost = 1;
	range = 2;
	attackStrategy = new NormalAttack(this);
	attackStrategy->setMaxNumOfTarget(1);
	attackStrategy->setTargetSelectionStrategy(TargetSelectionType::Random);
	auraEffect = new AuraEffect(this, AuraType::Null);
}
