#ifndef REGIONSELECTITEM_H
#define REGIONSELECTITEM_H

#include <QBrush>
#include <QPen>

#include "pixshotgraphicsitem.h"

class RegionSelect : public PixShotGraphicsItem
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
