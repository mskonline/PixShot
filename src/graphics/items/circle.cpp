#include "circle.h"
#include <QPainter>
#include <QGraphicsScene>

Circle::Circle(QGraphicsItem *parent)
    :isSelected(false)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    rTL = new QRectF(QPointF(0,0), QSizeF(8,8));
    rTR = new QRectF(QPointF(0,0), QSizeF(8,8));
    rBL = new QRectF(QPointF(0,0), QSizeF(8,8));
    rBR = new QRectF(QPointF(0,0), QSizeF(8,8));
}

void Circle::setOptions(ItemProperties *prop)
{
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;
}

QPainterPath Circle::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF Circle::boundingRect() const
{
    return QRectF(startPoint, endPoint);
}

void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* Draw mini boxes around the rectangle */
    isSelected = true;
    this->update();
}

void Circle::contextMenuEvent(QContextMenuEvent *e)
{
    //TODO
}

QVariant Circle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            isSelected = value.toBool();
    }

    this->update();
    return QGraphicsItem::itemChange(change, value);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rect = QRectF(startPoint,endPoint);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(rect.normalized());

    if(isSelected)
    {
        /* Set the Mini Selection Boxes around the Rectangle */
        painter->setPen(Qt::DashLine);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());

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

Circle::~Circle()
{
    delete rTL;
    delete rTR;
    delete rBL;
    delete rBR;
}
