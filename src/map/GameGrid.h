#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <vector>
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
	vector<vector<Cell*>> grid; // grid[row][col]
    QGraphicsScene* scene;
	TowerUtility towerUtility{this};
	EnemyUtility enemyUtility{this};
	PathFindingUtility pathFindingUtility{this};

    int numRows{0}, numCols{0}, numSpawns;
	set<Coordinate> spawns;
    set<Coordinate> blockedCells;
	Coordinate target;

	void destructMap(); // delete all cell

public:
	GPAManager gpaManager;
	WeekManager weekManager{this};
	ResourceManager resourceManager;

    GameGrid(QGraphicsScene* scene);
	~GameGrid();

	void loadMap(); // load default map
	void loadMap(const string& filename); // load custom map

	// getter
	Cell *getCell(int x, int y) const;
	Cell *getCell(Coordinate coordinate) const;

	int getNumRows() const;
	int getNumCols() const;

	const set<ITower*> &getAllTower() const;

	const set<IEnemy*> &getAllEnemy() const;

	QGraphicsScene *getScene() const;

	Path getPathStartEnd() const;

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

	void generateEnemy(EnemyType enemyType);

	QGraphicsRectItem* drawRange(TowerType towertype, Coordinate position);

    void clearBoard();
};

#endif // GAMEGRID_H
