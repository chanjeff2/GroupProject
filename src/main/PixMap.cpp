#include "PixMap.h"

PixMap::PixMap(const QPixmap &pixmap) {
	this->pixmap = new QGraphicsPixmapItem(pixmap);
}

PixMap::PixMap(QGraphicsPixmapItem *pixmap): pixmap(pixmap) {};

PixMap::~PixMap() {
	delete pixmap;
}

void PixMap::setVisible(bool visiblility) {
	pixmap->setVisible(visiblility);
}

void PixMap::setZValue(qreal z) {
	pixmap->setZValue(z);
}

void PixMap::setOffset(QPointF offset) {
	m_offset = offset;
	pixmap->setOffset(m_offset);
	emit offsetChange(m_offset);
}

void PixMap::setOffset(qreal x, qreal y) {
	setOffset(QPointF(x, y));
}

QPointF PixMap::offset() const {
	return m_offset;
}

bool PixMap::isVisible() const {
	return pixmap->isVisible();
}
