#include "arrow.h"

const qreal Pi = 3.14;

Arrow::Arrow(QGraphicsItem *parent)
    :isSelected(false)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    rT = new QRectF(QPointF(0,0), QSizeF(8,8));
    rB = new QRectF(QPointF(0,0), QSizeF(8,8));
}

void Arrow::undo()
{
    this->setVisible(0);
}

void Arrow::redo()
{
    this->setVisible(1);
}

void Arrow::setOptions(ItemProperties *prop)
{
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;

    // Always solid pattern for Arrow head
    this->brush.setStyle(Qt::SolidPattern);
}

/*QPainterPath Arrow::shape() const
{
    QPainterPath path(startPoint);
    path.lineTo(endPoint);
    path.addPolygon(arrowHead);

    return path;
}*/

QRectF Arrow::boundingRect() const
{
    qreal extra = (pn.width() + 20) / 2.0;
    return QRectF(startPoint, QSizeF(endPoint.x() - startPoint.x(),
                     endPoint.y() - startPoint.y())).normalized()
    .adjusted(-extra, -extra, extra, extra);
}

QVariant Arrow::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case QGraphicsItem::ItemSelectedHasChanged:
            isSelected = value.toBool();
    }

    this->update();
    return QGraphicsItem::itemChange(change, value);
}

/**
 * @brief Arrow::paint Overriding the paint function to draw the arrow
 * @param painter QPainter ptr
 * @param option QStyleOptionGraphicsItem ptr
 * @param widget QWidget ptr
 */
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);
    this->pn = pen;
    QLineF line(startPoint, endPoint);
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

        rT->moveCenter(startPoint);
        painter->drawRect(*rT);

        rB->moveCenter(endPoint);
        painter->drawRect(*rB);
    }

    prepareGeometryChange();
}
