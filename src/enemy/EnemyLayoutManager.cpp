#include "EnemyLayoutManager.h"

EnemyLayoutManager::EnemyLayoutManager() {}

EnemyLayoutManager::~EnemyLayoutManager() {
	delete this->imgView;
}

void EnemyLayoutManager::init(Coordinate coordinate) {
	this->imgView->setVisible(true);
	this->imgView->setZValue(static_cast<float>(Element::Enemy));
	moveTo(coordinate);
}

void EnemyLayoutManager::attachImageView(QGraphicsPixmapItem *imgView, Coordinate coordinate) {
	this->imgView = imgView;
	init(coordinate);
}

void EnemyLayoutManager::moveTo(int x, int y) {
	imgView->setOffset(x * CELL_SIZE.first, y * CELL_SIZE.second);
}

void EnemyLayoutManager::moveTo(Coordinate coordinate) {
	moveTo(coordinate.first, coordinate.second);
}
