#include "Path.h"

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
