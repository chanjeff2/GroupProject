#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#include <QObject>
#include <QGraphicsItemGroup>

class GraphicsItemGroup : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)

private:
	QPointF m_pos;
public:
	explicit GraphicsItemGroup(QObject *parent = nullptr);
    // position of the img group
    QPointF pos() const;
    void setPos(QPointF pos);
    void setPos(qreal x, qreal y);

signals:
	void posChanged(QPointF pos);

};

#endif // GRAPHICSITEMGROUP_H
