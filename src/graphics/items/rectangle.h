#ifndef RECTITEM_H
#define RECTITEM_H

#include <QPen>
#include <QMenu>
#include <QBrush>
#include <QPainterPath>
#include <QContextMenuEvent>

#include "pixshotgraphicsitem.h"

class Rectangle : public PixShotGraphicsItem
{
private:

    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rTL, *rTR, *rBL, *rBR;

public:

    Rectangle(QGraphicsItem *parent = 0);
    void setOptions(ItemProperties *prop);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ~Rectangle();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // RECTITEM_H
