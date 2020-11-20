#ifndef PATHFINDINGUTILITY_H
#define PATHFINDINGUTILITY_H

#include <deque>
#include <set>
using namespace std;

#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"

class PathFindingUtility
{
public:
	class Path { // change to pointer if needed
	public:
		deque<Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
		int pathStartEndDistance; // total number of cells in pathStartEnd
		Path();
	};

private:
	class PathBuffer {
	public:
		Path path; // calculated path for
		IEnemy *enemy; // corresponding enemy
	};

	const Cell *entry;
	const Cell *deadline;
	Path pathStartEnd; // path from entry to exit
	Path pathStartEndBuffer; // buffer to store preview
	set<PathBuffer*> pathBuffer; // buffer for each enemy

	Path findPath(const Cell *&start, const Cell *&End, const set<Cell*> &positionOfTowers);

	bool isEnemyOnPath(const IEnemy *&enemies, const Path &path);

public:
	PathFindingUtility();

	const Path getPathStartEnd() const;

	/* return buffer storing validated path for each enemy
	 * empty vector if not valid */
	bool validateTowerPlacement(const set<Cell*> &positionOfTowers, const set<IEnemy*> &enemies);

	/* successfully updated path -> true
	 * failed, path is blocked -> false */
	bool updatePath();
};

#endif // PATHFINDINGUTILITY_H
