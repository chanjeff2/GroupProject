#ifndef ENEMYLAYOUTMANAGER_H
#define ENEMYLAYOUTMANAGER_H

#include <QGraphicsPixmapItem>
#include "src/utility/GameValues.h"
#include "src/main/PixMap.h"

class EnemyLayoutManager
{
	PixMap *imgView{nullptr}; // img of enemy
	void init(); // call after attachImageView

public:
	EnemyLayoutManager();
	~EnemyLayoutManager();

	void attachImageView(PixMap *imgView);
	void moveTo(int x, int y, float interval = 0);
	void moveTo(Coordinate coordinate, float interval = 0);
};

#endif // ENEMYLAYOUTMANAGER_H
