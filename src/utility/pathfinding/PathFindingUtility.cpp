#include "PathFindingUtility.h"
#include "src/map/GameGrid.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"

#include <cmath>

// constructor
PathFindingUtility::PathFindingUtility(GameGrid *gameGrid): entry(gameGrid->getCell(START[0], START[1])), deadline(gameGrid->getCell(END[0], END[1])) {
	pathStartEnd = findPath(entry, deadline);
}

// methods

Path PathFindingUtility::processPath(CellDetails cellDetails[NUM_OF_COL][NUM_OF_ROW], const Cell *end) {
	Path path;

	int col = end->x;
	int row = end->y;

	bool reachStart = false;

	while (true) {
		path.pathStartEnd.push_front(gameGrid->getCell(col, row));
		path.pathStartEndDistance += 1;
		int temp_col = cellDetails[col][row].prevCell->x;
		int temp_row = cellDetails[col][row].prevCell->y;
		col = temp_col;
		row = temp_row;

		if (reachStart) {
			break;
		}

		if (cellDetails[col][row].prevCell == entry) {
			reachStart = true;
		}
	}

	return path;
}

Path PathFindingUtility::findPath(const Cell *start, const Cell *end, const set<ITower*> &Towers) {
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

	// init all cell
	for (int col = 0; col < NUM_OF_COL; ++col) {
		for (int row = 0; row < NUM_OF_ROW; ++row) {
			cellDetails[col][row].f = NUM_OF_COL * NUM_OF_ROW;
			cellDetails[col][row].g = NUM_OF_COL * NUM_OF_ROW;
			cellDetails[col][row].h = NUM_OF_COL * NUM_OF_ROW;
			cellDetails[col][row].prevCell = nullptr;
		}
	}

	// init start cell
	cellDetails[start->x][start->y].f = 0;
	cellDetails[start->x][start->y].g = 0;
	cellDetails[start->x][start->y].h = 0;
	cellDetails[start->x][start->y].prevCell = start;

	// open list for actual processing
	map<const Cell*, int /*f*/> openList;
	openList[start] = 0;

	// process loop
	while (!openList.empty()) {
		// randomly pick first element
		auto itCell = openList.begin();

		openList.erase(itCell);

		int _col = itCell->first->x;
		int _row = itCell->first->y;

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
				if (!gameGrid->isValidCoordinate(offseted_col, offseted_row)) {
					continue;
				}

				// reach destination
				if (offseted_col == end->x && offseted_row == end->y) {
					cellDetails[offseted_col][offseted_row].prevCell = gameGrid->getCell(_col, _row);
					path = processPath(cellDetails, end);
					return path;
				}

				// skip precessed or blocked cell
				if (closedList[offseted_col][offseted_row] == true || gameGrid->getCell(_col, _row)->hasTower()) {
					continue;
				}

				int gNew = cellDetails[_col][_row].g + 1.0;
				int hNew = abs(offseted_col - end->x) + abs(offseted_row - end->y);
				int fNew = gNew + hNew;

				// update openlist if not exist or get a better path
				if (cellDetails[offseted_col][offseted_row].f > fNew) {
					openList[gameGrid->getCell(offseted_col, offseted_row)] = fNew;
					cellDetails[offseted_col][offseted_row].g = gNew;
					cellDetails[offseted_col][offseted_row].h = hNew;
					cellDetails[offseted_col][offseted_row].f = fNew;
					cellDetails[offseted_col][offseted_row].prevCell = gameGrid->getCell(_col, _row);
				}
			}
		}
	}
	return path;
}

Path PathFindingUtility::findPath(const Cell *start, const Cell *end) {
	return findPath(start, end, gameGrid->getAllTower());
}

bool PathFindingUtility::isEnemyOnPath(const IEnemy *&enemies, const Path &path) {
	[psudo: if (path.contains(enemy->currentPosition))
		return true;
	else
		return false;]
}

const Path PathFindingUtility::getPathStartEnd() const {
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
