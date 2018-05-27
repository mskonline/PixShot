#ifndef REGIONSELECTITEM_H
#define REGIONSELECTITEM_H

#include <QBrush>
#include <QPen>

#include "baseitem.h"

class RegionSelectItem : public BaseItem
{
private:

    QPen pen;
    QBrush brush;

public:

    RegionSelectItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // REGIONSELECTITEM_H
