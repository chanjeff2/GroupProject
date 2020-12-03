#include "EnemyLayoutManager.h"
#include <QPropertyAnimation>
#include <QBrush>
#include <QDebug>

EnemyLayoutManager::EnemyLayoutManager() {}

EnemyLayoutManager::~EnemyLayoutManager() {
	delete this->imgViewGroup;
}

void EnemyLayoutManager::attachImageViews(GraphicsItemGroup *imgViewGroup, QGraphicsRectItem *hpBar, QGraphicsPixmapItem *imgView) {
	this->imgViewGroup = imgViewGroup;
	this->hpBar = hpBar;
	this->imgView = imgView;
}

void EnemyLayoutManager::moveTo(int x, int y, float interval) {
	if (interval == 0.0) {
		imgViewGroup->setPos(x * CELL_SIZE.first, y * CELL_SIZE.second);
		return;
	}

	QPropertyAnimation *animation = new QPropertyAnimation(imgViewGroup, "pos");
	animation->setDuration(interval);
	animation->setEndValue(QPointF(x * CELL_SIZE.first, y * CELL_SIZE.second));
	QObject::connect(animation, &QPropertyAnimation::finished, animation, &QPropertyAnimation::deleteLater);
	animation->start();
}

void EnemyLayoutManager::moveTo(Coordinate coordinate, float interval) {
	moveTo(coordinate.first, coordinate.second, interval);
}

void EnemyLayoutManager::setMaxHP(int max_hp) {
	m_max_hp = max_hp;
	setHP(max_hp);
}

void EnemyLayoutManager::setHP(int hp) {
	m_hp = hp;
	QRectF hp_rect = hpBar->rect();
	float hpRatio = static_cast<float>(m_hp) / m_max_hp;

	// resize hp bar according to hp ratio
	hp_rect.setWidth(HP_BAR_SIZE.first * hpRatio);
	hpBar->setRect(hp_rect);

	// change hp bar color according to hp ratio
	if (hpRatio < 0.3) {
		hpBar->setBrush(QColor(HP_BAR_RED.c_str())); // < 0.3 -> red
	} else if (hpRatio < 0.5) {
		hpBar->setBrush(QColor(HP_BAR_YELLOW.c_str())); // < 0.5 -> yellow
	} else {
		hpBar->setBrush(QColor(HP_BAR_GREEN.c_str())); // else -> green
	}
}

void EnemyLayoutManager::toggleRage(bool isRage) {
	if (img_path_rage == "") {
		qDebug() << "EnemyLayoutManager: toggle rage fail. Enemy rage image not yet set";
		return;
	}
	if (isRage) {
		this->imgView->setPixmap(QPixmap(img_path_rage));
	} else {
		this->imgView->setPixmap(QPixmap(img_path_normal));
	}
}

void EnemyLayoutManager::setImgPath(QString img_path_normal, QString img_path_rage) {
	this->img_path_normal = img_path_normal;
	this->img_path_rage = img_path_rage;
}
