#ifndef PATH_H
#define PATH_H

#include <deque>
using namespace std;

// forward declaration
class Cell;

class Path { // change to pointer if needed
	friend class PathFindingUtility; // for generating path

	// member data
	deque<const Cell*> pathStartEnd; // deque storing cells in subsequent order where pathStartEnd[0] is start
	int pathStartEndDistance{0}; // total number of cells in pathStartEnd
public:
	Path() = default;
	
	int getRemainingDistance() const;
	bool isNextCellEnd() const;
	const Cell *getCurrentCell() const;
	bool isEmpty() const;

	void goToNextCell();
};

#endif // PATH_H
