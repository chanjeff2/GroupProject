#include "TowerLayoutManager.h"

TowerLayoutManager::TowerLayoutManager() {}

TowerLayoutManager::~TowerLayoutManager() {
	delete this->imgView;
}

void TowerLayoutManager::init(Coordinate coordinate) {
	this->imgView->setVisible(true);
	this->imgView->setZValue(static_cast<float>(Element::Tower));
	moveTo(coordinate);
}

void TowerLayoutManager::attachImageView(QGraphicsPixmapItem *imgView, Coordinate coordinate) {
	this->imgView = imgView;
	init(coordinate);
}

void TowerLayoutManager::moveTo(int x, int y) {
	imgView->setOffset(x * CELL_SIZE.first, y * CELL_SIZE.second);
}

void TowerLayoutManager::moveTo(Coordinate coordinate) {
	moveTo(coordinate.first, coordinate.second);
}
