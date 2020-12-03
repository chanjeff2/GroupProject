#include "ITower.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/attack/IAttackStrategy.h"
#include "src/tower/aura/AuraEffect.h"
#include <cmath>
#include "src/utility/tower/TowerUtility.h"

QDebug& operator<<(QDebug &qdebug, const ITower &tower) {
	return qdebug << QString::fromStdString(tower.id);
}

// protected constructor -> prevent instantiation of ITower
ITower::ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType): position(position), towerUtility(towerUtility), towerType(towerType) {

}

// destructor
ITower::~ITower() {

}

void ITower::trigger() {
	// born to fight !
	long attackInterval = 1000/hitPerSec;
	attackInterval /= GAME_SPEED;

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &ITower::attack);
	timer->start(attackInterval);
}

void ITower::attack() {
	// do nothing if not implemented any attack Strategy
	if (attackStrategy == nullptr) {
		return;
	}

	// attack
	attackStrategy->attack();

	// get ready for next move
	float timeTilNextMove = 1000 / getHitPerSec();
	timeTilNextMove /= GAME_SPEED;

	if (timer->interval() != timeTilNextMove) {
		timer->setInterval(timeTilNextMove); // update timer interval in case there is change in speed;
	}
}

void ITower::remove() {
	timer->stop();
	delete attackStrategy;
	attackStrategy = nullptr;
	delete auraEffect;
	auraEffect = nullptr;
	this->deleteLater();
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

int ITower::getRange() const {
    return range;
}

set<EnemyType> ITower::getEffectiveTowards() const {
	return effectiveTowards;
}

set<EnemyType> ITower::getWeakTowards() const {
	return weakTowards;
}

// setter
void ITower::attachImageView(QGraphicsPixmapItem *imgView, QGraphicsRectItem* rangeView) {
    towerLayoutManager.attachImageView(imgView, rangeView, make_pair(position->x, position->y));
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
			if (!towerUtility->isValidCoordinate(position->x + dcol, position->y + drow)) {
				// skip invalid cell
				continue;
			}

			Cell *cell = towerUtility->getCell(position->x + dcol, position->y + drow);
			if (cell->getEnemy().empty()) {
				// skip empty cell
				continue;
			}

			auto enemyOnCell = cell->getEnemy();
			for (auto enemy: enemyOnCell) {
				enemyInRange.insert(enemy);
			}
		}
    }
	return enemyInRange;
}

QGraphicsRectItem* ITower::showRange(bool visibility) const {
	return this->towerLayoutManager.showRange(visibility);
}
