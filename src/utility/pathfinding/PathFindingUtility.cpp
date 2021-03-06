#include "PathFindingUtility.h"
#include "src/map/GameGrid.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"

#include <cmath>
#include <QDebug>
#include <queue>
#include <vector>

// constructor
PathFindingUtility::PathFindingUtility(GameGrid *gameGrid): gameGrid(gameGrid), entry(START), exit(END) {}

PathFindingUtility::PathBuffer::PathBuffer(Path path, IEnemy *enemy): path(path), enemy(enemy) {};

// methods
void PathFindingUtility::PathBuffer::flush() {
	try {
		qDebug() << "PathFindingUtility::PathBuffer: apply path buffer for" << *enemy;
		enemy->setPath(path);
		path.clear();
	}  catch (exception e) {
		qDebug() << "PathFindingUtility::PathBuffer: enemy probably deleted";
		qDebug() << "PathFindingUtility::PathBuffer:" << e.what();
	} catch (...) {
		qDebug() << "PathFindingUtility::PathBuffer: something bugged in flush";
	}
}


void PathFindingUtility::init() {
	this->numCols = NUM_OF_COL;
	this->numRows = NUM_OF_ROW;
	this->blockedPositions.clear();
	entry = START;
	exit = END;
	pathStartEnd = findPath(entry, exit);
}

void PathFindingUtility::init(int numCols, int numRows, Coordinate start, Coordinate end, set<Coordinate> blockedPositions) {
    this->numCols = numCols;
    this->numRows = numRows;
    this->blockedPositions = blockedPositions;
    entry = start;
    exit = end;
    pathStartEnd = findPath(start, end, blockedPositions);
}

Path PathFindingUtility::processPath(vector<vector<CellDetails>> cellDetails, const Coordinate end) {
	Path path;

	// start from end
	int col = end.first;
	int row = end.second;

	while (true) {
//		qDebug() << "col:" << col << "; row:" << row;
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
	if (blockedPosition.empty()) {
		return false;
	}
	return (blockedPosition.find(coordinate) != blockedPosition.end());
}

bool PathFindingUtility::isCoordinateBlocked(int x, int y, const set<Coordinate> &blockedPosition) const {
	if (blockedPosition.empty()) {
		return false;
	}
	return isCoordinateBlocked(make_pair(x, y), blockedPosition);
}

bool PathFindingUtility::isValidCoordinate(Coordinate coordinate) const {
    if (coordinate.first < 0 || coordinate.second < 0 || coordinate.first > numCols - 1 || coordinate.second > numRows - 1)
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
    bool closedList[numCols][numRows];

	// init all cell to false, indicating no cell is processed
    for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
			closedList[col][row] = false;
		}
	}

	// array holding cell details like coordinate and f, g, h values
	vector<vector<CellDetails>> cellDetails(numCols, vector<CellDetails>(numRows)); // cellDetails[col][row]

	// init start cell
	cellDetails[start.first][start.second].f = 0;
	cellDetails[start.first][start.second].g = 0;
	cellDetails[start.first][start.second].h = 0;

	// open list for actual processing
	queue<Coordinate> openList;
	openList.push(start);

	// process loop
	while (!openList.empty()) {
		// pick first element
		int _col = openList.front().first; // coordinate.col
		int _row = openList.front().second; // coordinate.row

		openList.pop();

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
					openList.push(make_pair(offseted_col, offseted_row));
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
	qDebug() << "PathFindingUtility: validate tower placement";
    // check from start to end
    set<Coordinate> invalidPositions;
    invalidPositions.insert(blockedPositions.begin(), blockedPositions.end());
    invalidPositions.insert(positionOfTowers.begin(), positionOfTowers.end());
    pathStartEndBuffer = findPath(entry, exit, invalidPositions );
	// clear and return if don't find any possible path from start to end
	if (pathStartEndBuffer.isEmpty()) {
		qDebug() << "PathFindingUtility: no path from start to end";
		for (auto element: pathBuffer) {
			// dellocate memory
			delete element;
		}
		pathBuffer.clear();
		pathStartEndBuffer.clear();
		return false;
	}

	// check for enemies not on optimized path
	set<IEnemy*> enemiesNotOnPath;
	//  hardcode copy_if
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		bool isOnPath = isEnemyOnPath(*it, pathStartEndBuffer);
		if (isOnPath) {
			Path _path = pathStartEndBuffer;
			while (_path.getCurrentCell() != (*it)->getPath().getCurrentCell()) {
				_path.goToNextCell();
			}
			PathBuffer *_pathBuffer = new PathBuffer(_path, *it);
			pathBuffer.insert(_pathBuffer); // add enemies on path to buffer
		} else {
			// reg it as not on Path
			enemiesNotOnPath.insert(*it);
		}
	}

	{
		// logging
		auto qdb = qDebug().nospace();
		qdb << "PathFindingUtility: enemies Not On Path { ";
		for (auto enemy: enemiesNotOnPath) {
			qdb << *enemy << " ";
		}
		qdb << "}";
	}

	// check for remaining enemies
	for (auto enemy: enemiesNotOnPath) {
        Path _path = findPath(enemy->getPath().getCurrentCoordinate(), exit, invalidPositions);
		if (!_path.isEmpty()) {
			PathBuffer *_pathBuffer = new PathBuffer(_path, enemy);
			pathBuffer.insert(_pathBuffer); // add enemies not on path to buffer
		} else {
			qDebug() << "PathFindingUtility: no path from start to end for" << *enemy;
			for (auto element: pathBuffer) {
				// dellocate memory
				delete element;
			}
			pathBuffer.clear(); // cannot find path for any enemy
			pathStartEndBuffer.clear();
			return false;
		}
	}

	return true;
}

/* successfully updated path -> true
 * failed, path is blocked -> false */
bool PathFindingUtility::updatePath() {
	qDebug() << "PathFindingUtility: update path";

	if (pathBuffer.empty() && pathStartEndBuffer.isEmpty()) {
		qDebug() << "PathFindingUtility: update path failed: no buffer exists";
		return false;
	}

	// all valid, replace enemies' pathToTake by path in buffer & clear buffer
	for (auto element: pathBuffer) {
		element->flush();
		// dellocate memory
		delete element;
	}
	pathBuffer.clear();

	// buffer content
	pathStartEnd = pathStartEndBuffer;
	pathStartEndBuffer.clear();

	return true;
}
