#include "ITower.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/attack/IAttackStrategy.h"
#include "src/tower/aura/AuraEffect.h"
#include <cmath>
#include "src/utility/tower/TowerUtility.h"

#include <QDebug>

// protected constructor -> prevent instantiation of ITower
ITower::ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType): position(position), towerUtility(towerUtility), towerType(towerType) {

}

// destructor
ITower::~ITower() {
	timer->stop();
	delete attackStrategy;
	delete auraEffect;
}

void ITower::trigger() {
	// born to fight !
	long attackInterval = 1000/hitPerSec;
	attackInterval /= GAME_SPEED;

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [&] {
		attackStrategy->attack();
	});
	timer->start(attackInterval);
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

// setter
void ITower::attachImageView(QGraphicsPixmapItem *imgView) {
	towerLayoutManager.attachImageView(imgView, make_pair(position->x, position->y));
}

// methods
set<IEnemy*> ITower::getEnemiesInRange() const {
	// TODO: get non occupied cells (in boundary) <- can open new function here
	// loop over all enemies, check if non occupied cells contain enemy current position
	// add enemy to buffer set if yes
	// return buffer set
	qDebug() << "get enemy in range";

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

			qDebug() << "col:" << cell->x << "; row:" << cell->y;

			auto enemyOnCell = cell->getEnemy();
			for (auto enemy: enemyOnCell) {
				enemyInRange.insert(enemy);
			}
		}
	}
	return enemyInRange;
}
