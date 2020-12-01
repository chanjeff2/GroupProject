#include "EnemyLayoutManager.h"
#include <QPropertyAnimation>

EnemyLayoutManager::EnemyLayoutManager() {}

EnemyLayoutManager::~EnemyLayoutManager() {
	delete this->imgView;
}

void EnemyLayoutManager::init() {
	this->imgView->setVisible(true);
	this->imgView->setZValue(static_cast<float>(Element::Enemy));
}

void EnemyLayoutManager::attachImageView(PixMap *imgView) {
	this->imgView = imgView;
	init();
}

void EnemyLayoutManager::moveTo(int x, int y, float interval) {
	if (interval == 0.0) {
		imgView->setOffset(x * CELL_SIZE.first, y * CELL_SIZE.second);
		return;
	}
	QPropertyAnimation animation(imgView, "offset");
	animation.setDuration(interval);
	animation.setEndValue(QPointF(x * CELL_SIZE.first, y * CELL_SIZE.second));
	animation.start();

}

void EnemyLayoutManager::moveTo(Coordinate coordinate, float interval) {
	moveTo(coordinate.first, coordinate.second, interval);
}
