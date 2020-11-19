#include "ITower.h"
#include <cmath>

// protected constructor -> prevent instantiation of ITower
ITower::ITower(Cell* position): position(position) {
	// born to fight !
	attackStrategy->attack();
}

// destructor
ITower::~ITower() {
	int redemption = round(cost * REDEMPTION_RATIO);
	ResourceManager.gainResource(redemption);
}

// getter
int ITower::getDamagePerHit() const {
	return damagePerHit;
}

float ITower::getHitPerSec() const {
	return hitPerSec;
}

set<EnemyType> ITower::getEffectiveTowards() const {
	return effectiveTowards;
}

set<EnemyType> ITower::getWeakTowards() const {
	return weakTowards;
}

// methods
set<IEnemy*> ITower::getEnemiesInRange() {
	// TODO: get non occupied cells (in boundary) <- can open new function here
	// loop over all enemies, check if non occupied cells contain enemy current position
	// add enemy to buffer set if yes
	// return buffer set
}
