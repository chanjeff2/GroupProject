#include "PathFindingUtility.h"
#include "src/map/GameGrid.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"

#include <cmath>

// constructor
PathFindingUtility::PathFindingUtility(GameGrid *gameGrid): gameGrid(gameGrid), entry(START), exit(END) {
	pathStartEnd = findPath(entry, exit);
}

PathFindingUtility::PathBuffer::PathBuffer(Path path, IEnemy *enemy): path(path), enemy(enemy) {};

// methods
Path PathFindingUtility::processPath(CellDetails cellDetails[NUM_OF_COL][NUM_OF_ROW], const Coordinate end) {
	Path path;

	// start from end
	int col = end.first;
	int row = end.second;

	while (true) {
		path.pathStartEnd.push_front(gameGrid->getCell(col, row));
		path.pathStartEndDistance += 1;

		// stop after getting start node
		if (cellDetails[col][row].prevCell == nullCoordinate) {
			break;
		}

		int temp_col = cellDetails[col][row].prevCell.first;
		int temp_row = cellDetails[col][row].prevCell.second;

		col = temp_col;
		row = temp_row;
	}

	return path;
}

bool PathFindingUtility::isCoordinateBlocked(Coordinate coordinate, const set<Coordinate> &blockedPosition) const {
	return (blockedPosition.find(coordinate) != blockedPosition.end());
}

bool PathFindingUtility::isCoordinateBlocked(int x, int y, const set<Coordinate> &blockedPosition) const {
	return isCoordinateBlocked(make_pair(x, y), blockedPosition);
}

bool PathFindingUtility::isValidCoordinate(Coordinate coordinate) const {
	if (coordinate.first < 0 || coordinate.second < 0 || coordinate.first > NUM_OF_COL - 1 || coordinate.second > NUM_OF_ROW - 1)
		return false;
	else
		return true;
}

bool PathFindingUtility::isValidCoordinate(int x, int y) const {
	return isValidCoordinate(make_pair(x, y));
}

Path PathFindingUtility::findPath(const Coordinate start, const Coordinate end, const set<Coordinate> &blockedPosition) {
	// no possible path return NULL
	// else return list of cells from start to end
	// * additional, return also the distance

	Path path;

	// closed list storing processed (used) cells
	bool closedList[NUM_OF_COL][NUM_OF_ROW];

	// init all cell to false, indicating no cell is processed
	for (int col = 0; col < NUM_OF_COL; ++col) {
		for (int row = 0; row < NUM_OF_ROW; ++row) {
			closedList[col][row] = false;
		}
	}

	// array holding cell details like coordinate and f, g, h values
	CellDetails cellDetails[NUM_OF_COL][NUM_OF_ROW];

	// init start cell
	cellDetails[start.first][start.second].f = 0;
	cellDetails[start.first][start.second].g = 0;
	cellDetails[start.first][start.second].h = 0;

	// open list for actual processing
	map<const Coordinate, int /*f*/> openList;
	openList[start] = 0; // insert start && set start.f = 0;

	// process loop
	while (!openList.empty()) {
		// randomly pick first element
		auto itCell = openList.begin();

		openList.erase(itCell);

		int _col = itCell->first.first; // coordinate.col
		int _row = itCell->first.second; // coordinate.row

		closedList[_col][_row] = true;

		// process all neighbour ** only 4 direction **
		for (int dcol = -1; dcol <= 1; ++dcol) {
			for (int drow = -1; drow <= 1; ++drow) {
				// skip diagonal neighbour
				if (abs(dcol) + abs(drow) > 1) {
					continue;
				}

				// skip self
				if (dcol == 0 && drow == 0) {
					continue;
				}

				int offseted_col = _col + dcol;
				int offseted_row = _row + drow;

				// skip out of range cell
				if (!isValidCoordinate(offseted_col, offseted_row)) {
					continue;
				}

				// reach destination
				if (offseted_col == end.first && offseted_row == end.second) {
					cellDetails[offseted_col][offseted_row].prevCell = make_pair(_col, _row);
					path = processPath(cellDetails, end);
					return path;
				}

				// skip precessed cell
				if (closedList[offseted_col][offseted_row] == true) {
					continue;
				}

				// skip blocked cell
				if (isCoordinateBlocked(offseted_col, offseted_row, blockedPosition)) {
					continue;
				}

				int gNew = cellDetails[_col][_row].g + 1.0;
				int hNew = abs(offseted_col - end.first) + abs(offseted_row - end.second);
				int fNew = gNew + hNew;

				// update openlist if not exist or get a better path
				if (cellDetails[offseted_col][offseted_row].f > fNew) {
					openList[make_pair(offseted_col, offseted_row)] = fNew;
					cellDetails[offseted_col][offseted_row].g = gNew;
					cellDetails[offseted_col][offseted_row].h = hNew;
					cellDetails[offseted_col][offseted_row].f = fNew;
					cellDetails[offseted_col][offseted_row].prevCell = make_pair(_col, _row);
				}
			}
		}
	}
	return path;
}

bool PathFindingUtility::isEnemyOnPath(const IEnemy *enemy, const Path &path) {
	if (find(path.pathStartEnd.begin(), path.pathStartEnd.end(), enemy->getPath().getCurrentCell()) != path.pathStartEnd.end())
		return true;
	else
		return false;
}

Path PathFindingUtility::getPathStartEnd() const {
	return pathStartEnd;
}

/* return buffer storing validated path for each enemy
 * empty vector if not valid */
bool PathFindingUtility::validateTowerPlacement(const set<Coordinate> &positionOfTowers, const set<IEnemy*> &enemies) {
	// check from start to end
	pathStartEndBuffer = findPath(entry, exit, positionOfTowers);
	// clear and return if don't find any possible path from start to end
	if (pathStartEndBuffer.isEmpty()) {
		pathBuffer.clear();
		return false;
	}

	// check for enemies not on optimized path
	set<IEnemy*> enemiesNotOnPath;
	//  hardcode copy_if
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		bool isOnPath = isEnemyOnPath(*it, pathStartEndBuffer);
		if (isOnPath) {
			if (isOnPath) {
				Path _path = pathStartEndBuffer;
				while (_path.getCurrentCell() != (*it)->getPath().getCurrentCell()) {
					_path.goToNextCell();
				}
				PathBuffer _pathBuffer(_path, *it);
				pathBuffer.insert(_pathBuffer); // add enemies on path to buffer
			} else {
				// reg it as not on Path
				enemiesNotOnPath.insert(*it);
			}
		}
	}

	// check for remaining enemies
	for (auto enemy: enemiesNotOnPath) {
		Path _path = findPath(enemy->getPath().getCurrentCoordinate(), exit, positionOfTowers);
		if (!_path.isEmpty()) {
			PathBuffer _pathBuffer(_path, enemy);
			pathBuffer.insert(_pathBuffer); // add enemies not on path to buffer
		} else {
			pathBuffer.clear(); // cannot find path for any enemy
			return false;
		}
	}

	return true;
}

/* successfully updated path -> true
 * failed, path is blocked -> false */
bool PathFindingUtility::updatePath() {

	if (pathBuffer.empty()) {
		return false;
	}

	// all valid, replace enemies' pathToTake by path in buffer & clear buffer
	for (auto element: pathBuffer) {
		element.enemy->setPath(element.path);
	}
	pathBuffer.clear();

	// buffer content
	pathStartEnd = pathStartEndBuffer;
	return true;
}
