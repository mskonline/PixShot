#ifndef CROPITEM_H
#define CROPITEM_H

#include <QBrush>
#include <QPen>
#include <QObject>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

#include "abstractitem.h"


class Crop : public AbstractItem
{
    Q_OBJECT
private:
    QPen pen, selectionPen;
    QBrush brush, selectionBrush;
    QGraphicsScene *scene;
    QWidget *Form;
    QPointF pixTop,
            cropStartPoint,
            cropEndPoint;
    void createTool();

public:
    QGraphicsProxyWidget *panel;
    QString temp;

    Crop(QGraphicsScene *scene,QGraphicsItem *parent = 0);
    ~Crop();
    void setOptions(ItemProperties *prop);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void crop();
    void cancel();

public slots:
    void emitCrop();
    void emitCancel();
};

#endif // CROPITEM_H
