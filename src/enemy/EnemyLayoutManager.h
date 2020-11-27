#ifndef ENEMYLAYOUTMANAGER_H
#define ENEMYLAYOUTMANAGER_H

#include <QGraphicsPixmapItem>
#include "src/utility/GameValues.h"

class EnemyLayoutManager
{
	QGraphicsPixmapItem *imgView{nullptr}; // img of enemy
	void init(Coordinate coordinate); // call after attachImageView

public:
	EnemyLayoutManager();
	~EnemyLayoutManager();

	void attachImageView(QGraphicsPixmapItem *imgView, Coordinate coordinate);
	void moveTo(int x, int y);
	void moveTo(Coordinate coordinate);
};

#endif // ENEMYLAYOUTMANAGER_H
