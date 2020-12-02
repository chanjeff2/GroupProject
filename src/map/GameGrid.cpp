#include "GameGrid.h"
#include "src/utility/GameValues.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/map/cell.h"
#include <fstream>

#include <QDebug>

GameGrid::GameGrid(QGraphicsScene* scene) : scene(scene) {
	// init grid
    numCols = NUM_OF_COL;
    numRows = NUM_OF_ROW;

    grid = new Cell**[NUM_OF_COL];
    cell_squares = new QGraphicsRectItem**[NUM_OF_COL];

    for ( int i = 0 ; i < NUM_OF_COL ; i++ ) {
        grid[i] = new Cell*[NUM_OF_ROW];
        cell_squares[i] = new QGraphicsRectItem*[NUM_OF_ROW];
    }

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
    for (int x = 0; x < numCols; ++x) {
        for (int y = 0; y < numRows; ++y) {
			delete grid[x][y]; // delete cells
            delete cell_squares[x][y];
		}
        delete [] grid[x];
        delete [] cell_squares[x];
	}
    delete [] grid;
    delete [] cell_squares;
}

void GameGrid::loadMap(QGraphicsScene *scene, const string &filename) {
    // delete old grid
    for ( int i = 0 ; i < numCols ; i++ ) {
        for ( int j = 0 ; j < numRows ; j++ ) {
            delete grid[i][j];
            cell_squares[i][j]->setVisible(false);
            scene->removeItem(cell_squares[i][j]);
            delete cell_squares[i][j];
        }
        delete [] grid[i];
        delete [] cell_squares[i];
    }

    delete [] grid;
    delete [] cell_squares;

    // load new grid
    ifstream map_file(filename);

    map_file >> numCols >> numRows;
    map_file >> ws;
    map_file >> noskipws;

    grid = new Cell**[numCols];
    cell_squares = new QGraphicsRectItem**[numCols];

    for( int i = 0 ; i < numCols ; i++ ) {
        grid[i] = new Cell*[numRows];
        cell_squares[i] = new QGraphicsRectItem*[numRows];
    }

    set<Coordinate> blockedPositions;

    for (int x = 0; x < numRows; ++x) {
        for (int y = 0; y < numCols; ++y) {
            // row and col flipped here

            char current_character;
            map_file >> current_character;
            CellType cell_type;

            switch (current_character) {
                case '#':
                    cell_type = CellType::BLOCKED;
                    blockedPositions.insert(make_pair(y,x));
                    break;
                case ' ':
                    cell_type = CellType::EMPTY;
                    break;
                case 'O':
                    cell_type = CellType::SPAWN;
                    blockedPositions.insert(make_pair(y,x));
                    break;
                case 'X':
                    cell_type = CellType::END;
                    blockedPositions.insert(make_pair(y,x));
                    break;
            }

            grid[y][x] = new Cell(y, x, cell_type);

            if (cell_type == CellType::SPAWN) {
                spawns.insert( grid[y][x] );
            }
            if (cell_type == CellType::END) {
                target = grid[y][x];
            }

            QBrush brushcolor;

            switch ( cell_type ) {
                case CellType::SPAWN:
                    brushcolor = Qt::green;
                    break;
                case CellType::END:
                    brushcolor = Qt::red;
                    break;
                case CellType::BLOCKED:
                    brushcolor = Qt::gray;
                    break;
                case CellType::EMPTY:
                    brushcolor = Qt::NoBrush;
                    break;
            }

            QGraphicsRectItem* square = scene->addRect(y*40, x*40, 40, 40, QPen(Qt::gray), brushcolor);

            cell_squares[y][x] = square;

        }
        map_file >> ws;
    }
    scene->setSceneRect( QRectF( 0, 0, numCols * CELL_SIZE.first, numRows * CELL_SIZE.second ) );
    pathFindingUtility.init( numCols, numRows, make_pair( (*spawns.begin())->x , (*spawns.begin())->y ), make_pair( target->x, target->y ) , blockedPositions );
}

// getter
Cell *GameGrid::getCell(int x, int y) const {
	if (!isValidCoordinate(x, y))
		return nullptr;

	return grid[x][y];
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

QGraphicsRectItem* GameGrid::drawRange(TowerType towertype, Coordinate position) {
	return this->towerUtility.drawRange(towertype, position);
}

void GameGrid::clearBoard() {
    towerUtility.removeAllTowers();
    enemyUtility.killAllEnemies();
}
