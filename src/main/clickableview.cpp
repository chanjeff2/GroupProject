#include <QMouseEvent>

#include "ClickableView.h"
#include "src/utility/GameValues.h"

ClickableView::ClickableView(QWidget *parent):QGraphicsView(parent) {}

void ClickableView::mousePressEvent(QMouseEvent *event) {
    // TODO: take the x, y position, convert to grid index and send the signal mouseClicked to GameWindow
    // NOTE the coordinate system:
    // +----------> x
    // |
    // |
    // |
    // v
    // y
    // Size of the image is 40x40
    // send signal: emit mouseClicked(int, int);
    QPointF clicked_pos = mapToScene(event->pos());
    int tile_x = static_cast<int>(clicked_pos.x())/CELL_SIZE.first;
    int tile_y = static_cast<int>(clicked_pos.y())/CELL_SIZE.second;
    emit mouseClicked(tile_x, tile_y);
    return;
}
