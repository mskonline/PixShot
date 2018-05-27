#ifndef HIGHLIGHTERITEM_H
#define HIGHLIGHTERITEM_H

#include <QBrush>
#include <QPen>

#include "baseitem.h"

class HighLighterItem : public BaseItem
{
private:

    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rTL, *rTR, *rBL, *rBR;

public:

    HighLighterItem(QGraphicsItem *parent = 0);
    void setOptions(ItemProperties *prop);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // HIGHLIGHTERITEM_H
