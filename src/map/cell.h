#ifndef CELL_H
#define CELL_H

#include <set>
using namespace std;

// forward declaration
class ITower;
class IEnemy;
class GameGrid;

class Cell
{
	friend class GameGrid; // cell can only be created when map init

	ITower *tower;
	set<IEnemy*> enemy;

	// constructor
	Cell(int x, int y);
	Cell(int x, int y, ITower *tower);

public:
	const int x;
	const int y;

	ITower *getTower() const;
	set<IEnemy*> getEnemy() const;

	// methods
	// true -> successfully placed
	bool placeTower(ITower *tower);
	void removeTower();

	void addEnemy(IEnemy *enemy);
	void removeEnemy(IEnemy *enemy);

	// no enemy nor tower
	bool isEmpty() const;

	bool hasTower() const;
};

#endif // CELL_H
