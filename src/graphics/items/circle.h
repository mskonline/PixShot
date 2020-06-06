#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QPen>
#include <QMenu>
#include <QBrush>
#include <QPainterPath>
#include <QContextMenuEvent>

#include "pixshotgraphicsitem.h"

class Circle : public PixShotGraphicsItem
{
private:

    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rTL, *rTR, *rBL, *rBR;

public:

    Circle(QGraphicsItem *parent = 0);
    void setOptions(ItemProperties *prop);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ~Circle();

private:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};
#endif // CIRCLEITEM_H
