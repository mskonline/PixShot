#ifndef REGIONSELECTITEM_H
#define REGIONSELECTITEM_H

#include <QBrush>
#include <QPen>

#include "abstractitem.h"

class RegionSelect : public AbstractItem
{
private:
    QPen pen;
    QBrush brush;

public:
    RegionSelect(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // REGIONSELECTITEM_H
