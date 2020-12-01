#ifndef TOWERUTILITY_H
#define TOWERUTILITY_H

#include <set>
#include <QGraphicsRectItem>

using namespace std;

#include "src/utility/GameValues.h"

// forward declaration
class ITower;
class Cell;
enum class TowerType;
class GameGrid;

class TowerUtility
{
    GameGrid *gameGrid;
	int towerID_index{0}; // debug
public:
	static set<ITower*> refOfTowers; // ref of all towers
	static set<ITower*> refOfAuraTowers; // ref of all tower with aura
    static QGraphicsRectItem* drawRange(Coordinate position, TowerType tower_type , QGraphicsScene& scene);
	set<Coordinate> positionOfTowers;

	TowerUtility(GameGrid *gameGrid);
    ~TowerUtility();

    void placeTower(TowerType towerType, Cell *position);

    void removeTower(Cell *position);

	Cell *getCell(int x, int y) const;
	int getCost(TowerType towerType) const;
	bool isValidCoordinate(int x, int y) const;
};

#endif // TOWERUTILITY_H
