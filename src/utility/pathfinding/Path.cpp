#include "Path.h"

void Path::goToNextCell() {
	pathStartEnd.pop_front();
	--pathStartEndDistance;
}

int Path::getRemainingDistance() {
	return pathStartEndDistance;
}

bool Path::isNextCellEnd() {
	return pathStartEndDistance <= 2;
}

Cell *Path::getCurrentCell() {
	return pathStartEnd.at(0);
}
