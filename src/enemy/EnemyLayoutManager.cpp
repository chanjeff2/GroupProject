#include "EnemyLayoutManager.h"

EnemyLayoutManager::EnemyLayoutManager() {}

EnemyLayoutManager::~EnemyLayoutManager() {
	delete this->imgView;
}

void EnemyLayoutManager::init() {
	this->imgView->setVisible(true);
	this->imgView->setZValue(static_cast<float>(Element::Enemy));
	moveTo(START);
}

void EnemyLayoutManager::attachImageView(QGraphicsPixmapItem *imgView) {
	this->imgView = imgView;
	init();
}

void EnemyLayoutManager::moveTo(int x, int y) {
	imgView->setOffset(x * CELL_SIZE.first, y * CELL_SIZE.second);
}

void EnemyLayoutManager::moveTo(Coordinate coordinate) {
	moveTo(coordinate.first, coordinate.second);
}
