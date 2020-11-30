#include "GameGrid.h"
#include "src/utility/GameValues.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/map/cell.h"

GameGrid::GameGrid(QGraphicsScene* scene) : scene(scene) {
	// init grid
	for (int x = 0; x < NUM_OF_COL; ++x) {
		for (int y = 0; y < NUM_OF_ROW; ++y) {
            grid[x][y] = new Cell(x, y);

            QBrush brushcolor(Qt::NoBrush);
            if (x == 0 && y == 0)
                brushcolor = Qt::green;
            else if (x == NUM_OF_COL - 1 && y == NUM_OF_ROW - 1)
                brushcolor = Qt::red;

            QGraphicsRectItem* square = scene->addRect(x*40, y*40, 40, 40, QPen(Qt::gray), brushcolor);
            cell_squares[x][y] = square;
        }
	}
	pathFindingUtility.init();
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
Cell *GameGrid::getCell(int x, int y) const {
	if (!isValidCoordinate(x, y))
		return nullptr;

	return grid[x][y];
}

const set<ITower*> &GameGrid::getAllTower() const {
	return towerUtility.refOfTowers;
}

const set<IEnemy*> &GameGrid::getAllEnemy() const {
	return enemyUtility.enemies;
}

QGraphicsScene *GameGrid::getScene() const {
	return scene;
}

Path GameGrid::getPathStartEnd() const {
	return pathFindingUtility.getPathStartEnd();
}

// methods
bool GameGrid::isValidCoordinate(int x, int y) const {
	if (x < 0 || y < 0 || x > NUM_OF_COL - 1 || y > NUM_OF_ROW - 1)
		return false;

	return true;
}

/* can place -> true
 * can't, i.e. cell contain tower/enemy/will block path -> false */
bool GameGrid::canPlaceTower(int x, int y) {
	Cell *cell = grid[x][y];
	set<IEnemy*> enemies = enemyUtility.enemies;

	Coordinate newPos = make_pair(x, y);

	// check if place at start or end
	if (newPos == START || newPos == END) {
		return false;
	}

	// Check if the cell is occupied with tower
	if (cell->tower != NULL) {
		return false;
	}

	// check if the cell is occupied with any enemy
	for (auto enemy: enemies) {
		if (enemy->getPath().getCurrentCoordinate() == newPos)
			return false;
	}

	set<Coordinate> newTowerPositions = towerUtility.positionOfTowers;
	newTowerPositions.insert(newPos);

	// validate path
	if (!pathFindingUtility.validateTowerPlacement(newTowerPositions, enemies)) {
		return false;
	}

	return true;
}

/* success -> true
 * fail -> false */
bool GameGrid::placeTower(int x, int y, TowerType towerType) {
	// check if enough resource
	if (resourceManager.getResource() < towerUtility.getCost(towerType)) {
		return false;
	}

	if (canPlaceTower(x, y)) {
		Cell *cell = grid[x][y];
		towerUtility.placeTower(towerType, cell);
		// update path
		pathFindingUtility.updatePath();
		// spend resource
		resourceManager.spendResource(towerUtility.getCost(towerType));
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
	pathFindingUtility.validateTowerPlacement(towerUtility.positionOfTowers, enemyUtility.enemies);
	pathFindingUtility.updatePath();

	return true;
}

void GameGrid::generateEnemy(EnemyType enemyType) {
	this->enemyUtility.generateEnemy(enemyType);
}
