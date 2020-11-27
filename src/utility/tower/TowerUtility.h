#ifndef TOWERUTILITY_H
#define TOWERUTILITY_H

#include <set>
using namespace std;

#include "src/utility/GameValues.h"

// forward declaration
class ITower;
class Cell;
class GameGrid;

class TowerUtility
{
	GameGrid *gameGrid;
public:
	static set<ITower*> refOfTowers; // ref of all towers
	static set<ITower*> refOfAuraTowers; // ref of all tower with aura
	set<Coordinate> positionOfTowers;

	TowerUtility(GameGrid *gameGrid);
    ~TowerUtility();

    void placeTower(TowerType towerType, Cell *position);

    void removeTower(Cell *position);

	Cell *getCell(int x, int y) const;
};

#endif // TOWERUTILITY_H
