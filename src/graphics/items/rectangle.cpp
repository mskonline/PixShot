#include "rectangle.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

Rectangle::Rectangle(QGraphicsItem *parent)
    :isSelected(false)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    rTL = new QRectF(QPointF(0,0),QSizeF(8,8));
    rTR = new QRectF(QPointF(0,0),QSizeF(8,8));
    rBL = new QRectF(QPointF(0,0),QSizeF(8,8));
    rBR = new QRectF(QPointF(0,0),QSizeF(8,8));
}

void Rectangle::setOptions(ItemProperties *prop)
{
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;
}

QPainterPath Rectangle::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(spoint,epoint);
}

void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* Draw mini boxes around the rectangle */

    isSelected = true;
    this->update();
}

void Rectangle::contextMenuEvent(QContextMenuEvent *e)
{
    //TODO
    QMenu menu;
    menu.addMenu("hello");
    menu.exec(e->globalPos());
}

QVariant Rectangle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            isSelected = value.toBool();
    }

    this->update();
    return QGraphicsItem::itemChange(change,value);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(spoint,epoint).normalized());

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

Rectangle::~Rectangle()
{
    delete rTL;
    delete rTR;
    delete rBL;
    delete rBR;
}
