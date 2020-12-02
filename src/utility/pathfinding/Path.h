#ifndef PATH_H
#define PATH_H

#include <deque>
#include <QDebug>
using namespace std;

#include "src/utility/GameValues.h"

// forward declaration
class Cell;
class IEnemy;

class Path { // change to pointer if needed
	friend class PathFindingUtility; // for generating path
	friend QDebug &operator<<(QDebug &qdebug, const Path &path);

	// member data
	deque<Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
	int pathStartEndDistance{0}; // total number of cells in pathStartEnd
public:
	Path() = default;

    // for debugging, print the whole path
    void print() const;

	int getRemainingDistance() const;
	bool isNextCellEnd() const;
	Cell *getCurrentCell() const;
	const Coordinate getCurrentCoordinate() const;
	Cell *getNextCell() const;
	const Coordinate getNextCoordinate() const;
	bool isEmpty() const;

	void goToNextCell(IEnemy* enemy = nullptr);
	void clear();
};

// for debugging, print the whole path

#endif // PATH_H
