#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <array>
#include <set>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
using namespace std;

#include "src/utility/tower/TowerUtility.h"
#include "src/utility/enemy/EnemyUtility.h"
#include "src/utility/pathfinding/PathFindingUtility.h"
#include "src/utility/GameValues.h"

#include "src/utility/GPA/GPAManager.h"
#include "src/utility/week/WeekManager.h"
#include "src/utility/resource/ResourceManager.h"


class GameGrid
{
	array<array<Cell*, NUM_OF_ROW>, NUM_OF_COL> grid; // get element: grid[x][y]
	TowerUtility towerUtility{this};
	EnemyUtility enemyUtility{this};
	PathFindingUtility pathFindingUtility{this};

public:
	GPAManager gpaManager;
	WeekManager weekManager;
	ResourceManager resourceManager;

	GameGrid();
	~GameGrid();

	// getter
	Cell *getCell(int x, int y) const;

	const set<ITower*> &getAllTower() const;

	const set<IEnemy*> &getAllEnemy() const;

	// methods
	bool isValidCoordinate(int x, int y) const;

	/* can place -> true
	 * can't, i.e. cell contain tower/enemy/will block path -> false */
	bool canPlaceTower(int x, int y);

	/* success -> true
	 * fail -> false */
	bool placeTower(int x, int y, TowerType towerType);

	/* successfully remove tower -> true
	 * failed -> false */
	bool removeTower(int x, int y);
};

#endif // GAMEGRID_H
