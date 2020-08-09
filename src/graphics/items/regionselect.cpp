#include "regionselect.h"
#include <QPainter>

RegionSelect::RegionSelect(QGraphicsItem *parent)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setOpacity(0.75);
    //this->pen = pen();
    this->brush = QBrush(QColor(225, 225, 0, 150),Qt::SolidPattern);
}

QRectF RegionSelect::boundingRect() const
{
    return QRectF(startPoint, endPoint);
}

void RegionSelect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(startPoint, endPoint).normalized());
}
