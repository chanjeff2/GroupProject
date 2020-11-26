#include "Path.h"
#include "src/map/cell.h"

void Path::goToNextCell() {
	pathStartEnd.pop_front();
	--pathStartEndDistance;
}

int Path::getRemainingDistance() const {
	return pathStartEndDistance;
}

bool Path::isNextCellEnd() const {
	return pathStartEndDistance <= 2;
}

const Cell *Path::getCurrentCell() const {
	return pathStartEnd.at(0);
}

bool Path::isEmpty() const {
	return pathStartEndDistance == 0;
}

const Coordinate Path::getCurrentCoordinate() const {
	return make_pair(getCurrentCell()->x, getCurrentCell()->y);
}
