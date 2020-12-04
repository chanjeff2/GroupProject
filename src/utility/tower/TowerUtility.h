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
    GameGrid *gameGrid; // keep pointer to the game grid to access the scene, check coordinates, and update resource manager
	int towerID_index{0}; // debug
public:
	// data member
	static set<ITower*> refOfTowers; // ref of all towers
	static set<ITower*> refOfAuraTowers; // ref of all tower with aura
    set<Coordinate> positionOfTowers; // keep track of positions of towers to prevent invalid placement

	// construct & destructor
	TowerUtility(GameGrid *gameGrid);
    ~TowerUtility();

	// tower placement and removal
    void placeTower(TowerType towerType, Cell *position);
    void removeTower(Cell *position);
    void removeAllTowers();

	// getter
	Cell *getCell(int x, int y) const;

	// utility
    int getCost(TowerType towerType) const; // returns cost of a particular type of tower
    int getRange(TowerType towerType) const; // returns range of a particular type of tower
    bool isValidCoordinate(int x, int y) const; // check if coordinate is not blocked by tower or obstacle
    QGraphicsRectItem* drawRange(ITower *tower, Cell *position); // display range of placed tower
    QGraphicsRectItem* drawRange(TowerType towertype, Coordinate position); // display range of previewed tower prior to purchase
    QGraphicsRectItem* drawRange(int range, AuraType aura_type, Coordinate position, bool isPreview); // display aura range
};

#endif // TOWERUTILITY_H
