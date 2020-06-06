#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsItem>
#include <QUndoCommand>
#include "../../commons/commons.h"

class PixShotGraphicsItem : public QGraphicsItem, public QObject
{
public:
    QPointF spoint,epoint;

    PixShotGraphicsItem();
    virtual void setOptions(ItemProperties *props) {};
};

#endif // BASEITEM_H
