#ifndef ENEMYLAYOUTMANAGER_H
#define ENEMYLAYOUTMANAGER_H

#include <QGraphicsPixmapItem>
#include "src/utility/GameValues.h"
#include "src/main/GraphicsItemGroup.h"

class EnemyLayoutManager
{
    GraphicsItemGroup *imgViewGroup{nullptr}; // img group of enemy
	void init(); // call after attachImageView

public:
	EnemyLayoutManager();
	~EnemyLayoutManager();

	void attachImageView(GraphicsItemGroup *imgView);
	void moveTo(int x, int y, float interval = 0);
	void moveTo(Coordinate coordinate, float interval = 0);
	void setHP(int hp);
};

#endif // ENEMYLAYOUTMANAGER_H
