#ifndef HIGHLIGHTERITEM_H
#define HIGHLIGHTERITEM_H

#include <QBrush>
#include <QPen>

#include "abstractitem.h"

class HighLighter : public AbstractItem
{
private:
    QPen pen;
    QBrush brush;
    bool isSelected;
    QRectF *rTL, *rTR, *rBL, *rBR;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    HighLighter(QGraphicsItem *parent = 0);
    void setOptions(ItemProperties *prop);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // HIGHLIGHTERITEM_H
