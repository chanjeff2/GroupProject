#ifndef PATH_H
#define PATH_H

#include <deque>
using namespace std;

#include "src/utility/GameValues.h"

// forward declaration
class Cell;
class IEnemy;

class Path { // change to pointer if needed
	friend class PathFindingUtility; // for generating path

	// member data
	deque<Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
	int pathStartEndDistance{0}; // total number of cells in pathStartEnd
public:
	Path() = default;
	
	int getRemainingDistance() const;
	bool isNextCellEnd() const;
	Cell *getCurrentCell() const;
	const Coordinate getCurrentCoordinate() const;
	bool isEmpty() const;

	void goToNextCell(IEnemy* enemy = nullptr);
};

#endif // PATH_H
