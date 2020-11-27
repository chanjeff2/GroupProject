#include "ITower.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/attack/IAttackStrategy.h"
#include "src/tower/aura/AuraEffect.h"
#include <cmath>
#include "src/utility/tower/TowerUtility.h"

// protected constructor -> prevent instantiation of ITower
ITower::ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType): position(position), towerUtility(towerUtility), towerType(towerType) {
	// born to fight !
	long attackInterval = 1000/hitPerSec;
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [&] {
		attackStrategy->attack();
	});
	timer->start(attackInterval);
}

// destructor
ITower::~ITower() {
	timer->stop();
	delete attackStrategy;
	delete auraEffect;
}

// getter
TowerType ITower::getTowerType() const {
	return towerType;
}

int ITower::getDamagePerHit() const {
	return damagePerHit;
}

float ITower::getHitPerSec() const {
	return hitPerSec;
}

int ITower::getCost() const {
	return cost;
}

set<EnemyType> ITower::getEffectiveTowards() const {
	return effectiveTowards;
}

set<EnemyType> ITower::getWeakTowards() const {
	return weakTowards;
}

// methods
set<IEnemy*> ITower::getEnemiesInRange() const {
	// TODO: get non occupied cells (in boundary) <- can open new function here
	// loop over all enemies, check if non occupied cells contain enemy current position
	// add enemy to buffer set if yes
	// return buffer set
	set<IEnemy*> enemyInRange;
	for (int dcol = -range; dcol <= range; ++dcol) {
		for (int drow = -range; drow <= range; ++drow) {
			Cell *cell = towerUtility->getCell(position->x + dcol, position->y + drow);
			enemyInRange.insert(cell->getEnemy().begin(), cell->getEnemy().end());
		}
	}
	return enemyInRange;
}
