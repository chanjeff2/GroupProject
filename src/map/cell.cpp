#include "cell.h"
#include "GameGrid.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"

QDebug& operator<<(QDebug &qdebug, const Cell &cell) {
	qdebug.nospace() << "(" << cell.x << ", " << cell.y << "); "
					 << "tower { ";
	if (cell.hasTower()) {
		qdebug << *(cell.tower);
	}
	qdebug << " }; "
	<< "enemy { ";
	if (!cell.enemy.empty()) {
		auto it = cell.enemy.begin();
		qdebug << **it;
		++it;
		for (; it != cell.enemy.end(); ++it) {
			qdebug << ", " << **it;
		}
	}
	qdebug << " };";
	return qdebug.space();
}

Cell::Cell(int x, int y): x(x), y(y), tower(nullptr) , cell_type(CellType::EMPTY) {};

Cell::Cell(int x, int y, ITower *tower): x(x), y(y), tower(tower) , cell_type(CellType::BLOCKED) {};

Cell::Cell(int x, int y, CellType cell_type): x(x), y(y), cell_type(cell_type) {};

// getter
ITower *Cell::getTower() const {
	return this->tower;
}

set<IEnemy*> Cell::getEnemy() const {
	return this->enemy;
}

// methods
// true -> successfully placed
bool Cell::placeTower(ITower *tower) {
	if (this->tower != nullptr) {
		return false;
	} else {
		this->tower = tower;
		return true;
	}
}

void Cell::removeTower() {
	delete this->tower;
	this->tower = nullptr;
}

void Cell::addEnemy(IEnemy *enemy) {
	this->enemy.insert(enemy);
}

void Cell::removeEnemy(IEnemy *enemy) {
	this->enemy.erase(enemy);
}

// no enemy nor tower
bool Cell::isEmpty() const {
	if (this->tower != nullptr || !enemy.empty()) {
		return false;
	} else {
		return true;
	}
}

bool Cell::hasTower() const {
	return this->tower != nullptr;
}
