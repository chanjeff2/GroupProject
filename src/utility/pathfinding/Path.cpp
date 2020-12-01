#include "Path.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/GameValues.h"

#include <QDebug>

void Path::goToNextCell(IEnemy* enemy) {
	// un reg from current cell
	if (enemy != nullptr) {
		pathStartEnd.at(0)->removeEnemy(enemy);
	}

	pathStartEnd.pop_front();
	--pathStartEndDistance;

	// reg into new cell
	if (enemy != nullptr) {
		qDebug() << "Path:" << *enemy << "moved to" << *getCurrentCell();
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

const Coordinate Path::getCurrentCoordinate() const {
	return make_pair(getCurrentCell()->x, getCurrentCell()->y);
}

Cell *Path::getNextCell() const {
	if (pathStartEndDistance < 2) {
		return nullptr;
	}
	return pathStartEnd.at(1);
}

const Coordinate Path::getNextCoordinate() const {
	if (pathStartEndDistance < 2) {
		return nullCoordinate;
	}
	return make_pair(getNextCell()->x, getNextCell()->y);
}

bool Path::isEmpty() const {
	return pathStartEndDistance == 0;
}

void Path::clear() {
	pathStartEnd.clear();
	pathStartEndDistance = 0;
}
