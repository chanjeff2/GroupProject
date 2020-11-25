#ifndef PATH_H
#define PATH_H

#include <deque>
using namespace std;

// forward declaration
class Cell;

class Path { // change to pointer if needed
	friend class PathFindingUtility; // for generating path

	// member data
	deque<Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
	int pathStartEndDistance; // total number of cells in pathStartEnd
public:
	Path() = default;
	void goToNextCell();
	int getRemainingDistance();
	bool isNextCellEnd();
	Cell *getCurrentCell();
};

#endif // PATH_H
