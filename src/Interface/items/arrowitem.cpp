#include "arrowitem.h"

const qreal Pi = 3.14;

ArrowItem::ArrowItem(QGraphicsItem *parent)
    :isSelected(false)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    rT = new QRectF(QPointF(0,0),QSizeF(8,8));
    rB = new QRectF(QPointF(0,0),QSizeF(8,8));
}

void ArrowItem::undo()
{
    this->setVisible(FALSE);
}

void ArrowItem::redo()
{
    this->setVisible(TRUE);
}

void ArrowItem::setOptions(ItemProperties *prop)
{
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;

    // Always solid pattern for Arrow head
    this->brush.setStyle(Qt::SolidPattern);
}

/*QPainterPath ArrowItem::shape() const
{
    QPainterPath path(spoint);
    path.lineTo(epoint);
    path.addPolygon(arrowHead);

    return path;
}*/

QRectF ArrowItem::boundingRect() const
{
    qreal extra = (pn.width() + 20) / 2.0;
    return QRectF(spoint, QSizeF(epoint.x() - spoint.x(),
                     epoint.y() - spoint.y())).normalized()
    .adjusted(-extra, -extra, extra, extra);
}

QVariant ArrowItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            isSelected = value.toBool();
    }

    this->update();
    return QGraphicsItem::itemChange(change,value);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);
    this->pn = pen;
    QLineF line(spoint,epoint);
    qreal arrowSize = 20;

    double angle = ::acos(line.dx() / line.length());

    if (line.dy() >= 0)
        angle = (Pi * 2) - angle;

    arrowP1 = line.p2() - QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
    arrowP2 = line.p2() - QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);


    arrowHead.clear();
    arrowHead << line.p2() << arrowP1 << arrowP2;
    painter->drawLine(line);
    painter->drawPolygon(arrowHead);

    if(isSelected)
    {
        QPen p;
        p.setColor(QColor(Qt::green));

        QBrush b;
        b.setStyle(Qt::SolidPattern);
        b.setColor(QColor(Qt::green));
        painter->setPen(p);
        painter->setBrush(b);

        rT->moveCenter(spoint);
        painter->drawRect(*rT);

        rB->moveCenter(epoint);
        painter->drawRect(*rB);
    }

    prepareGeometryChange();
}
