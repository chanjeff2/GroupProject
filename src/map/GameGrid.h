#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <array>
#include <set>
using namespace std;

#include "src/utility/TowerUtility.h"
#include "src/utility/EnemyUtility.h"
#include "src/utility/PathFindingUtility.h"
#include "src/utility/GameValues.h"


class GameGrid
{
	static array<array<Cell*, NUM_OF_ROW>, NUM_OF_COL> grid; // get element: grid[x][y]
	TowerUtility towerUtility;
	EnemyUtility enemyUtility;
	PathFindingUtility pathFindingUtility;

public:
	GameGrid();
	~GameGrid();

	// getter
	static const Cell *getCell(int x, int y);

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
