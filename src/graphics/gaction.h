#ifndef GACTION_H
#define GACTION_H

#include <QGraphicsItem>
#include "../commons/commons.h"

class GAction {

   public:
    GAction();

    QGraphicsItem *item;
    int action;
    QVariant vt;
};

#endif // GACTION_H
