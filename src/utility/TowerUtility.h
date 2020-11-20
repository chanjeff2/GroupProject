#ifndef TOWERUTILITY_H
#define TOWERUTILITY_H

#include <set>
using namespace std;

#include "GameValues.h"
#include "src/map/cell.h"

// forward declaration
class ITower;

class TowerUtility
{
public:
	set<ITower*> refOfTowers; // ref of all towers
	set<Cell*> positionOfTowers;

    TowerUtility();
    ~TowerUtility();

    void placeTower(TowerType towerType, Cell *position);

    void removeTower(Cell *position);
};

#endif // TOWERUTILITY_H
