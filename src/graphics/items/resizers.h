#ifndef RESIZERS_H
#define RESIZERS_H
#include "abstractitem.h"

class Resizers: public AbstractItem
{
public:
    Resizers();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RESIZERS_H
