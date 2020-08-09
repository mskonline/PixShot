#ifndef RECTITEM_H
#define RECTITEM_H
#include <QPen>
#include <QMenu>
#include <QBrush>
#include <QPainterPath>
#include <QContextMenuEvent>
#include "abstractitem.h"

class Rectangle : public AbstractItem
{
private:
    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rTL, *rTR, *rBL, *rBR;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    Rectangle(QGraphicsItem *parent = 0);
    void setOptions(ItemProperties *prop);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ~Rectangle();
};

#endif // RECTITEM_H
