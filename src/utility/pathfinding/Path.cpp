#include "Path.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"

void Path::goToNextCell(IEnemy* enemy) {
	// un reg from current cell
	if (enemy != nullptr) {
		pathStartEnd.at(0)->removeEnemy(enemy);
	}

	pathStartEnd.pop_front();
	--pathStartEndDistance;

	// reg into new cell
	if (enemy != nullptr) {
		pathStartEnd.at(0)->addEnemy(enemy);
	}
}

int Path::getRemainingDistance() const {
	return pathStartEndDistance;
}

bool Path::isNextCellEnd() const {
	return pathStartEndDistance <= 2;
}

Cell *Path::getCurrentCell() const {
	return pathStartEnd.at(0);
}

bool Path::isEmpty() const {
	return pathStartEndDistance == 0;
}

const Coordinate Path::getCurrentCoordinate() const {
	return make_pair(getCurrentCell()->x, getCurrentCell()->y);
}

void Path::clear() {
	pathStartEnd.clear();
	pathStartEndDistance = 0;
}
