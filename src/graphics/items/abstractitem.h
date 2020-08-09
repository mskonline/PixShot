#ifndef BASEITEM_H
#define BASEITEM_H
#include <QGraphicsItem>
#include <QUndoCommand>
#include "../../commons/commons.h"

class AbstractItem : public QGraphicsItem, public QObject
{
protected:
    QPointF startPoint;
    QPointF endPoint;

public:
    AbstractItem();
    inline void setStartPoint(QPointF);
    inline QPointF getStartPoint() const;
    inline void setEndPoint(QPointF);
    inline QPointF getEndPoint() const;

    virtual void setOptions(ItemProperties *) {};
};

inline void AbstractItem::setStartPoint(QPointF point)
{
    startPoint = point;
};

inline QPointF AbstractItem::getStartPoint() const
{
    return startPoint;
}

inline void AbstractItem::setEndPoint(QPointF point)
{
    endPoint = point;
}

inline QPointF AbstractItem::getEndPoint() const
{
    return endPoint;
}


#endif // BASEITEM_H
