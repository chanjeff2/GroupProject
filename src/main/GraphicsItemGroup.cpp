#include <QBrush>
#include <QDebug>
#include "GraphicsItemGroup.h"
#include "src/utility/GameValues.h"

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

void GraphicsItemGroup::setMaxHP(int max_hp) {
    m_max_hp = max_hp;
    setHP(max_hp);
}

void GraphicsItemGroup::setHPBar(QGraphicsRectItem *hp_bar) {
    this->hp_bar = hp_bar;
}

void GraphicsItemGroup::setHP(int hp) {
    m_hp = hp;
    QRectF hp_rect = hp_bar->rect();
    float hpRatio = static_cast<float>(m_hp) / m_max_hp;

    // resize hp bar according to hp ratio
    hp_rect.setWidth(HP_BAR_SIZE.first * hpRatio);
    hp_bar->setRect(hp_rect);

    // change hp bar color according to hp ratio
    if (hpRatio < 0.3) {
        hp_bar->setBrush(QColor(HP_BAR_RED.c_str())); // < 0.3 -> red
    } else if (hpRatio < 0.5) {
        hp_bar->setBrush(QColor(HP_BAR_YELLOW.c_str())); // < 0.5 -> yellow
    } else {
        hp_bar->setBrush(QColor(HP_BAR_GREEN.c_str())); // else -> green
    }
}
