#ifndef TOWERLAYOUTMANAGER_H
#define TOWERLAYOUTMANAGER_H

#include <QGraphicsPixmapItem>
#include "src/utility/GameValues.h"

class TowerLayoutManager
{
	QGraphicsPixmapItem *imgView{nullptr}; // img of enemy
    QGraphicsRectItem *rangeView{nullptr};
	void init(Coordinate coordinate); // call after attachImageView

public:
	TowerLayoutManager();
	~TowerLayoutManager();

    void attachImageView(QGraphicsPixmapItem *imgView, QGraphicsRectItem *rangeView, Coordinate coordinate);
	void moveTo(int x, int y);
	void moveTo(Coordinate coordinate);
	QGraphicsRectItem* showRange(bool visibility) const;
};

#endif // TOWERLAYOUTMANAGER_H
