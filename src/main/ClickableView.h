#ifndef CLICKABLEVIEW_H
#define CLICKABLEVIEW_H

#include <QGraphicsView>

class ClickableView : public QGraphicsView
{
    Q_OBJECT
public:
    ClickableView(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void mouseClicked(int x, int y);
};

#endif // CLICKABLEVIEW_H
