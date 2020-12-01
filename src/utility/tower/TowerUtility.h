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
	// data member
	static set<ITower*> refOfTowers; // ref of all towers
	static set<ITower*> refOfAuraTowers; // ref of all tower with aura
	set<Coordinate> positionOfTowers;

	// construct & destructor
	TowerUtility(GameGrid *gameGrid);
    ~TowerUtility();

	// tower placement and removal
    void placeTower(TowerType towerType, Cell *position);
    void removeTower(Cell *position);

	// getter
	Cell *getCell(int x, int y) const;

	// utility
	int getCost(TowerType towerType) const;
	int getRange(TowerType towerType) const;
	bool isValidCoordinate(int x, int y) const;
	QGraphicsRectItem* drawRange(ITower *tower, Cell *position);
	QGraphicsRectItem* drawRange(TowerType towertype, Coordinate position);
	QGraphicsRectItem* drawRange(int range, AuraType aura_type, Coordinate position, bool isPreview);
};

#endif // TOWERUTILITY_H
