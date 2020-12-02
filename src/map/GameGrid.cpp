#include "GameGrid.h"
#include "src/utility/GameValues.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/map/cell.h"
#include <fstream>

#include <QDebug>

GameGrid::GameGrid(QGraphicsScene* scene) : scene(scene) {
	loadMap();
}

GameGrid::~GameGrid() {
	// delete grid
	destructMap();
}

void GameGrid::destructMap() {
	qDebug() << "GameGrid: destruct map";
	// clear cell
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			delete grid[row][col]; // delete cells
			grid[row][col] = nullptr;
		}
		grid[row].clear();
	}
	grid.clear();

	// clear ui
	scene->clear();

	// clear spawns, target, block
	spawns.clear();
	target = nullCoordinate;
	blockedCells.clear();
}

void GameGrid::loadMap() {
	// delete old grid
	destructMap();
	qDebug() << "GameGrid: load default map";
	// init default grid
	numCols = NUM_OF_COL;
	numRows = NUM_OF_ROW;

	grid.resize(numRows, vector<Cell*>(numCols));

	for (int col = 0; col < NUM_OF_COL; ++col) {
		for (int row = 0; row < NUM_OF_ROW; ++row) {
			grid[row][col] = new Cell(col, row);

			QBrush brushcolor(Qt::NoBrush);
			// set color for start and end
			if (make_pair(col, row) == START) {
				brushcolor = Qt::green;
			} else if (make_pair(col, row) == END) {
				brushcolor = Qt::red;
			}

			grid[row][col]->cell_squares = scene->addRect(col * CELL_SIZE.first, row * CELL_SIZE.second, CELL_SIZE.first, CELL_SIZE.second, QPen(Qt::gray), brushcolor);
		}
	}
	scene->setSceneRect( QRectF( 0, 0, numCols * CELL_SIZE.first, numRows * CELL_SIZE.second ) );
	pathFindingUtility.init();
}

void GameGrid::loadMap(const string &filename) {
    // delete old grid
	destructMap();
	qDebug() << "GameGrid: load map from" << filename.c_str();

    // load new grid
    ifstream map_file(filename);

	map_file >> noskipws; // prevent skipping space
	// init col and row
	numRows = 0;
	numCols = 0;

	int row = 0;

	while (!map_file.eof()) {
		int col = 0;
		vector<Cell*> rows;
		string input;
		getline(map_file, input);
		for (char &current_character: input) {
            CellType cell_type;
			QBrush brushcolor;

			Cell *newCell = new Cell(col, row);

            switch (current_character) {
                case '#':
                    cell_type = CellType::BLOCKED;
					brushcolor = Qt::gray;
					blockedCells.insert(make_pair(col, row));
                    break;
                case 'O':
                    cell_type = CellType::SPAWN;
					brushcolor = Qt::green;
					blockedCells.insert(make_pair(col, row));
					spawns.insert(make_pair(col, row));
                    break;
                case 'X':
                    cell_type = CellType::END;
					brushcolor = Qt::red;
					blockedCells.insert(make_pair(col, row));
					target = make_pair(col, row);
                    break;
				default: // case ' '
					cell_type = CellType::EMPTY;
					brushcolor = Qt::NoBrush;
					break;
            }

			newCell->setCellType(cell_type);
			rows.push_back(newCell);

			newCell->cell_squares = scene->addRect(col * CELL_SIZE.first, row * CELL_SIZE.second, CELL_SIZE.first, CELL_SIZE.second, QPen(Qt::gray), brushcolor);

			// proceed to next char
			++col;
		}
		grid.push_back(rows);
		map_file >> ws; // skip line
		++numRows;
		++row;
    }
	if (numRows == 0) {
		qDebug() << "GameGrid: failed to load map from" << filename.c_str();
		loadMap();
		return;
	}
	grid.shrink_to_fit(); // trunc extra row
	for (auto row: grid) {
		row.shrink_to_fit(); // trunc extra col
	}
	numCols = (grid[0].empty()) ? 0 : grid[0].size();
	qDebug() << "GameGrid: no. of col:" << numCols << "; no. of row:" << numRows;
	// reload default map if no spawn point
	if (spawns.empty()) {
		qDebug() << "GameGrid: no spawn point is found in" << filename.c_str();
		loadMap();
		return;
	}
	if (target == nullCoordinate) {
		qDebug() << "GameGrid: no exit is found in" << filename.c_str();
		loadMap();
		return;
	}
	scene->setSceneRect( QRectF( 0, 0, numCols * CELL_SIZE.first, numRows * CELL_SIZE.second) );
	Coordinate start = *spawns.begin();
	pathFindingUtility.init(numCols, numRows, start, target, blockedCells);
}

// getter
Cell *GameGrid::getCell(int x, int y) const {
	if (!isValidCoordinate(x, y))
		return nullptr;

	return grid[y][x];
}

Cell *GameGrid::getCell(Coordinate coordinate) const {
	return getCell(coordinate.first, coordinate.second);
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
    if (x < 0 || y < 0 || x > numCols - 1 || y > numRows - 1)
		return false;

	return true;
}

/* can place -> true
 * can't, i.e. cell contain tower/enemy/will block path -> false */
bool GameGrid::canPlaceTower(int x, int y) {
    if ( blockedCells.find(make_pair(x, y)) != blockedCells.end() ) {
        return false;
    }

	Cell *cell = getCell(x, y);
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
		Cell *cell = getCell(x, y);
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
	Cell *cell = getCell(x, y);
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

QGraphicsRectItem* GameGrid::drawRange(TowerType towertype, Coordinate position) {
	return this->towerUtility.drawRange(towertype, position);
}

void GameGrid::clearBoard() {
    gpaManager.toggle_game_started(false);
    weekManager.toggle_game_started(false);
    enemyUtility.killAllEnemies();
    towerUtility.removeAllTowers();
    pathFindingUtility.validateTowerPlacement(towerUtility.positionOfTowers, enemyUtility.enemies);
    pathFindingUtility.updatePath();
}
