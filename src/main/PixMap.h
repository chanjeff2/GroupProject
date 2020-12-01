#ifndef PIXMAP_H
#define PIXMAP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>

class PixMap: public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
	Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChange)

signals:
	void offsetChange(QPointF offset);

private:
	QGraphicsPixmapItem *pixmap;
	QPointF m_offset;
public:
	PixMap(const QPixmap &pixmap);

	PixMap(QGraphicsPixmapItem *pixmap);

	~PixMap();

	void setVisible(bool visiblility);

	void setZValue(qreal z);

	void setOffset(QPointF offset);

	void setOffset(qreal x, qreal y);

	QPointF offset() const;

	bool isVisible() const;

};

#endif // PIXMAP_H
