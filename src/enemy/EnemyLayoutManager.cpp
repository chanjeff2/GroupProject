#include "EnemyLayoutManager.h"
#include <QPropertyAnimation>

EnemyLayoutManager::EnemyLayoutManager() {}

EnemyLayoutManager::~EnemyLayoutManager() {
	delete this->imgViewGroup;
}

void EnemyLayoutManager::attachImageView(GraphicsItemGroup *imgView) {
	this->imgViewGroup = imgView;
}

void EnemyLayoutManager::moveTo(int x, int y, float interval) {
	if (interval == 0.0) {
		imgViewGroup->setPos(x * CELL_SIZE.first, y * CELL_SIZE.second);
		return;
	}

	QPropertyAnimation *animation = new QPropertyAnimation(imgViewGroup, "pos");
	animation->setDuration(interval);
	animation->setEndValue(QPointF(x * CELL_SIZE.first, y * CELL_SIZE.second));
	QObject::connect(animation, &QPropertyAnimation::finished, animation, &QPropertyAnimation::deleteLater);
	animation->start();
}

void EnemyLayoutManager::moveTo(Coordinate coordinate, float interval) {
	moveTo(coordinate.first, coordinate.second, interval);
}

void EnemyLayoutManager::setHP(int hp) {
	imgViewGroup->setHP(hp);
}
