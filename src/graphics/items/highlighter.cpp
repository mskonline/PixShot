#include "highlighter.h"
#include <QPainter>

HighLighter::HighLighter(QGraphicsItem *parent)
    :isSelected(false)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setOpacity(0.75);
    //this->pen = pen();
    this->brush = QBrush(QColor(225,225,0,150),Qt::SolidPattern);
    this->pen.setWidth(0);
    this->pen.setColor(QColor(225,225,0,150));

    rTL = new QRectF(QPointF(0,0), QSizeF(8,8));
    rTR = new QRectF(QPointF(0,0), QSizeF(8,8));
    rBL = new QRectF(QPointF(0,0), QSizeF(8,8));
    rBR = new QRectF(QPointF(0,0), QSizeF(8,8));
}

void HighLighter::setOptions(ItemProperties *prop)
{
    /* IGNORE
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;
    */
}

QRectF HighLighter::boundingRect() const
{
    return QRectF(startPoint, endPoint);
}

void HighLighter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* Draw mini boxes around the rectangle */
    isSelected = true;
    this->update();
}

QVariant HighLighter::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            isSelected = value.toBool();
    }

    this->update();
    return QGraphicsItem::itemChange(change, value);
}

void HighLighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(startPoint, endPoint).normalized());

    if(isSelected)
    {
        /* Set the Mini Selection Boxes around the Rectangle */
        QRectF rect = boundingRect();

        QPen p;
        p.setColor(QColor(Qt::green));

        QBrush b;
        b.setStyle(Qt::SolidPattern);
        b.setColor(QColor(Qt::green));
        painter->setPen(p);
        painter->setBrush(b);

        rTL->moveCenter(rect.topLeft());
        painter->drawRect(*rTL);

        rTR->moveCenter(rect.topRight());
        painter->drawRect(*rTR);

        rBL->moveCenter(rect.bottomLeft());
        painter->drawRect(*rBL);

        rBR->moveCenter(rect.bottomRight());
        painter->drawRect(*rBR);
    }
}
