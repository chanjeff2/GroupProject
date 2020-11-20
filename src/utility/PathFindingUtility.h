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
private:
	class Path {
	public:
		deque<Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
		int pathStartEndDistance; // total number of cells in pathStartEnd
		Path();
	};

	class PathBuffer {
	public:
		Path path; // calculated path for
		IEnemy *enemy; // corresponding enemy
	};

	const Cell *entry = GridUtility.getCell(START[0], START[1]);
	const Cell *deadline = GridUtility.getCell(END[0], END[1]);
	Path pathStartEnd; // path from entry to exit
	set<Cell*> pathStartEndBuffer; // buffer to store preview
	set<PathBuffer*> pathBuffer; // buffer for each enemy

	deque<Cell*> *findPath(Cell *start, Cell *End, vector<Cell*> positionOfTowers) {
		// no possible path return empty vector
		// else return vector list of cells from start to end
		// * additional, return also the distance
	}

	Bool isEnemyOnPath(IEnemy *enemies, std::vector<Cell*> path) {
		[psudo: if (path.contains(enemy->currentPosition))
			return true;
		else
			return false;]
	}

public:
	PathFindingUtility() {
		pathStartEnd = findPath(entry, deadline, TowerUtility.positionOfTowers)
	}

	std::vector<Cell*> getPathStartEnd() {
		return pathStartEnd;
	}

	/* return buffer storing validated path for each enemy
	 * empty vector if not valid */
	Bool validateTowerPlacement(vector<Cell*> positionOfTowers = TowerUtility.positionOfTowers) {
		// get list of enemies
		vector<IEnemy*> enemies = EnemyUtility.enemies;

		// check from start to end
		pathStartEndBuffer = findPath(entry, deadline, positionOfTowers);
		if (pathStartEnd == Nullptr) {
			pathBuffer.clear();
			return false;
		}

		// check for enemies not on optimized path
		[psudo: vector<IEnemy*> enemiesNotOnPath = enemies.filter({ enemy ->
			Bool isOnPath = isEnemyOnPath(enemy, pathStartEndBuffer); // true -> on path
			if (isOnPath)
				std::vector<Cell*> tempPath = ... // pop until the start is current position
				pathBuffer.push_back({enemy, tempPath, tempPath.size()}); // better to return the distance when calculate path instead of using size()
			else
				return true; // insert enemies not on path to enemiesNotOnPath
		})]

		// check for remaining enemies
		[psudo: forEach(enemiesNotOnPath) { enemy ->
			std::vector<Cell*> path = findPath(enemy->currentPosition, deadline, positionOfTowers);
			if (!path.empty()) {
				pathBuffer.push_back({enemy, path, path.size()}); // better to return the distance when calculate path instead of using size()
			} else {
				pathBuffer.clear();
				return false;
			}
		}]
		return true;
	}

	/* successfully updated path -> true
	 * failed, path is blocked -> false */
	bool updatePath() {

		if (pathBuffer.empty()) {
			return false;
		}

		// all valid, replace enemies' pathToTake by path in buffer & clear buffer
		forEach(pathBuffer) { element ->
			element.enemy.pathToTake = element.path;
			element.enemy.distanceFromEnd
		}
		pathBuffer.clear();

		// buffer content & clear buffer
		pathStartEnd = pathStartEndBuffer;
		pathStartEndBuffer.clear();
		return true;
	}
};

#endif // PATHFINDINGUTILITY_H
