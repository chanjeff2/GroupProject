#ifndef TOWERUTILITY_H
#define TOWERUTILITY_H

#include <set>

#include "src/tower/implementation/Regular.h"
#include "src/tower/implementation/Arts.h"
#include "src/tower/implementation/WolframAlpha.h"
#include "src/tower/implementation/Hacker.h"
#include "src/tower/implementation/Calc.h"
#include "src/tower/implementation/Nerd.h"
#include "src/tower/implementation/Ghostwriter.h"
#include "src/tower/implementation/Chegg.h"

using namespace std;

typedef pair<int /*col*/, int /*row*/> Coordinate;

// forward declaration
class ITower;
class Cell;
enum class TowerType;
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
