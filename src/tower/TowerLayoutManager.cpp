#include "TowerLayoutManager.h"

TowerLayoutManager::TowerLayoutManager() {}

TowerLayoutManager::~TowerLayoutManager() {
	delete this->imgView;
	delete this->rangeView;
}

void TowerLayoutManager::init(Coordinate coordinate) {
	this->imgView->setVisible(true);
	this->imgView->setZValue(static_cast<float>(Element::Tower));
	moveTo(coordinate);
}

void TowerLayoutManager::attachImageView(QGraphicsPixmapItem *imgView, QGraphicsRectItem* rangeView, Coordinate coordinate) {
    this->rangeView = rangeView;
	this->imgView = imgView;
	init(coordinate);
}

void TowerLayoutManager::moveTo(int x, int y) {
	imgView->setOffset(x * CELL_SIZE.first, y * CELL_SIZE.second);
}

void TowerLayoutManager::moveTo(Coordinate coordinate) {
	moveTo(coordinate.first, coordinate.second);
}

QGraphicsRectItem* TowerLayoutManager::showRange(bool visibility) const {
    this->rangeView->setVisible(visibility);
    return this->rangeView;
}
