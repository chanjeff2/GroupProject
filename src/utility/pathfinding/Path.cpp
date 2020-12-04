#include "Path.h"
#include "src/map/cell.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/GameValues.h"

QDebug &operator<<(QDebug &qdebug, const Path &path) {
	qdebug.nospace() << "path { ";
	for (auto cell: path.pathStartEnd) {
		qdebug << "(" << cell->x << ", " << cell->y << ") ";
	}
	qdebug << "};";
	return qdebug.space();
}

void Path::goToNextCell(IEnemy* enemy) {
	try {
		if (isEmpty()) {
			qDebug() << "Path: empty path for" << *enemy;
			return;
		}

		if (pathStartEndDistance <= 1) {
			qDebug() << "Path: path missing next cell for" << *enemy;
			return;
		}

		// un reg from current cell
		if (enemy != nullptr) {
			pathStartEnd.at(0)->removeEnemy(enemy);
		}
		pathStartEnd.pop_front();
		--pathStartEndDistance;

		// reg into new cell
		if (enemy != nullptr) {
//			qDebug() << "Path:" << *enemy << "moved to" << *getCurrentCell(); // comment out to avoid spam
			pathStartEnd.at(0)->addEnemy(enemy);
		}
	}  catch (exception e) {
		qDebug() << "Path: error when go to next cell:" << e.what();
	} catch (...) {
		qDebug() << "Path: error when go to next cell, not sure reason";
	}

}

int Path::getRemainingDistance() const {
	return pathStartEndDistance;
}

bool Path::isNextCellEnd() const {
	return pathStartEndDistance <= 2;
}

Cell *Path::getCurrentCell() const {
	if (isEmpty()) {
		return nullptr;
	}
	return pathStartEnd.at(0);
}

const Coordinate Path::getCurrentCoordinate() const {
	return make_pair(getCurrentCell()->x, getCurrentCell()->y);
}

Cell *Path::getNextCell() const {
	if (pathStartEndDistance <= 1) {
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
	return pathStartEnd.empty();
}

void Path::clear() {
	pathStartEnd.clear();
	pathStartEndDistance = 0;
}
