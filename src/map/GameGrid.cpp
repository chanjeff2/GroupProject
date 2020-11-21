#include "GameGrid.h"
#include "src/utility/GameValues.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/map/cell.h"

GameGrid::GameGrid() {
	// init grid
	for (int x = 0; x < NUM_OF_COL; ++x) {
		for (int y = 0; y < NUM_OF_ROW; ++y) {
			grid[x][y] = new Cell(x, y);
		}
	}
}
GameGrid::~GameGrid() {
	// delete grid
	// and also all positible pointer?
	for (int x = 0; x < NUM_OF_COL; ++x) {
		for (int y = 0; y < NUM_OF_ROW; ++y) {
			delete grid[x][y]; // delete cells
		}
	}

}

// getter
const Cell *GameGrid::getCell(int x, int y) {
	return grid[x][y];
}

/* can place -> true
 * can't, i.e. cell contain tower/enemy/will block path -> false */
bool GameGrid::canPlaceTower(int x, int y) {
	Cell *cell = grid[x][y];
	set<IEnemy*> enemies = enemyUtility.enemies;

	// Check if the cell is occupied with tower
	if (cell->tower != NULL) {
		return false;
	}

	// check if the cell is occupied with any enemy
	for (auto enemy: enemies) {
		if (enemy->getPathToTake()[0]->x == x && enemy->getPathToTake()[0]->y == y)
			return false;
	}

	set<Cell*> newTowerPositions = towerUtility.positionOfTowers;
	newTowerPositions.insert(cell);

	// validate path
	if (!pathFindingUtility.validateTowerPlacement(newTowerPositions)) {
		return false;
	}

	return true;
}

/* success -> true
 * fail -> false */
bool GameGrid::placeTower(int x, int y, TowerType towerType) {
	if (canPlaceTower(x, y)) {
		Cell *cell = grid[x][y];
		towerUtility.placeTower(towerType, cell);
		return true;
	}
	return false;
}

/* successfully remove tower -> true
 * failed -> false */
bool GameGrid::removeTower(int x, int y) {
	Cell *cell = grid[x][y];
	// check if have tower
	if (cell->tower == nullptr)
		return false;

	// remove
	towerUtility.removeTower(cell);

	// update path of enemies
	pathFindingUtility.validateTowerPlacement(towerUtility.positionOfTowers);
	pathFindingUtility.updatePath();

	return true;
}
