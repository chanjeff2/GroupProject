#include "PathFindingUtility.h"
#include "src/map/GameGrid.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"

// constructor
PathFindingUtility::PathFindingUtility(const set<Cell*> &positionOfTowers): entry(GameGrid::getCell(START[0], START[1])), deadline(GameGrid::getCell(END[0], END[1])) {
	pathStartEnd = findPath(entry, deadline, positionOfTowers);
}

// methods

PathFindingUtility::Path PathFindingUtility::findPath(const Cell *&start, const Cell *&End, const set<Cell*> &positionOfTowers) {
	// no possible path return NULL
	// else return list of cells from start to end
	// * additional, return also the distance
}

bool PathFindingUtility::isEnemyOnPath(const IEnemy *&enemies, const Path &path) {
	[psudo: if (path.contains(enemy->currentPosition))
		return true;
	else
		return false;]
}

const PathFindingUtility::Path PathFindingUtility::getPathStartEnd() const {
	return pathStartEnd;
}

/* return buffer storing validated path for each enemy
 * empty vector if not valid */
bool PathFindingUtility::validateTowerPlacement(const set<Cell*> &positionOfTowers, const set<IEnemy*> &enemies) {
	// check from start to end
	pathStartEndBuffer = findPath(entry, deadline, positionOfTowers);
	if (pathStartEnd == NULL) {
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
bool PathFindingUtility::updatePath() {

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

// PathFindingUtility::Path
void PathFindingUtility::Path::goToNextCell() {
	pathStartEnd.pop_front();
	--pathStartEndDistance;
}

int PathFindingUtility::Path::getRemainingDistance() {
	return pathStartEndDistance;
}

bool PathFindingUtility::Path::isNextCellEnd() {
	return pathStartEndDistance <= 2;
}

Cell *PathFindingUtility::Path::getCurrentCell() {
	return pathStartEnd.at(0);
}
