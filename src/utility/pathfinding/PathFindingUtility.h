#ifndef PATHFINDINGUTILITY_H
#define PATHFINDINGUTILITY_H

#include <deque>
#include <set>
using namespace std;

#include "Path.h"
#include "src/utility/GameValues.h"

// forward declaration
class Cell;
class ITower;
class IEnemy;
class GameGrid;

class PathFindingUtility
{
private:
	class PathBuffer {
	public:
		Path path; // calculated path for
		IEnemy *enemy; // corresponding enemy
	};
	
	class CellDetails {
	public:
		const Cell *prevCell; // previous cell **start from end**
		int f; // f = g + h
		int g; // cost from start to this cell
		int h; // cost from this cell to end
	};

	const Cell *entry;
	const Cell *deadline;
	Path pathStartEnd; // path from entry to exit
	Path pathStartEndBuffer; // buffer to store preview
	set<PathBuffer*> pathBuffer; // buffer for each enemy
	const GameGrid *gameGrid; // ref to game grid

	Path processPath(CellDetails cellDetails[NUM_OF_COL][NUM_OF_ROW], const Cell *end);

	Path findPath(const Cell *start, const Cell *end, const set<ITower*> &Towers);
	Path findPath(const Cell *start, const Cell *end);

	bool isEnemyOnPath(const IEnemy *&enemies, const Path &path);

public:
	PathFindingUtility(GameGrid *gameGrid);

	const Path getPathStartEnd() const;

	/* return buffer storing validated path for each enemy
	 * empty vector if not valid */
	bool validateTowerPlacement(const set<Cell*> &positionOfTowers, const set<IEnemy*> &enemies);

	/* successfully updated path -> true
	 * failed, path is blocked -> false */
	bool updatePath();
};

#endif // PATHFINDINGUTILITY_H
