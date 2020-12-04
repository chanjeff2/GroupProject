#ifndef ENEMYLAYOUTMANAGER_H
#define ENEMYLAYOUTMANAGER_H

#include <QGraphicsPixmapItem>
#include "src/utility/GameValues.h"
#include "src/main/GraphicsItemGroup.h"

class EnemyLayoutManager
{
    GraphicsItemGroup *imgViewGroup{nullptr}; // img group of enemy
	QString img_path_normal = "";
	QString img_path_rage = "";
	int m_max_hp;
	int m_hp;
	QGraphicsRectItem *hpBar{nullptr};
	QGraphicsPixmapItem *imgView{nullptr};

	void init(); // call after attachImageView

public:
	EnemyLayoutManager();
	~EnemyLayoutManager();

	// movement
	void moveTo(int x, int y, float interval = 0);
	void moveTo(Coordinate coordinate, float interval = 0);
	// set hp and max hp
	void setMaxHP(int max_hp);
	void setHP(int hp);
	// rage
	void toggleRage(bool isRage);
	// attach img view
	void attachImageViews(GraphicsItemGroup *imgViewGroup, QGraphicsRectItem *hpBar, QGraphicsPixmapItem *imgView);
	void setImgPath(QString img_path_normal = "", QString img_path_rage = "");
};

#endif // ENEMYLAYOUTMANAGER_H
