#ifndef ARROWITEM_H
#define ARROWITEM_H
#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QPen>
#include <math.h>
#include "abstractitem.h"

class Arrow : public AbstractItem
{
private:
    QPolygonF arrowHead;
    QPen pn;
    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rT, *rB;
    QPointF arrowP1, arrowP2;

public:
    Arrow(QGraphicsItem *parent = 0);
    void undo();
    void redo();
    void setOptions(ItemProperties *prop);
    QRectF boundingRect() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ARROWITEM_H
