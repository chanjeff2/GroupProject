#include "GraphicsItemGroup.h"

GraphicsItemGroup::GraphicsItemGroup(QObject *parent) : QObject(parent), QGraphicsItemGroup() {}

QPointF GraphicsItemGroup::pos() const {
    return m_pos;
}

void GraphicsItemGroup::setPos(QPointF pos) {
    m_pos = pos;
    QGraphicsItemGroup::setPos(pos);
}

void GraphicsItemGroup::setPos(qreal x, qreal y) {
    setPos(QPoint(x, y));
}
