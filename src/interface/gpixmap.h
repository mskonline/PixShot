#ifndef GPIXMAP_H
#define GPIXMAP_H

#include "gaction.h"
#include <QStack>
#include <QGraphicsPixmapItem>

class GPixMap : public QGraphicsPixmapItem
{
public:

    bool notifiedChange;
    int zoomStep;
    qreal scale;

    explicit GPixMap(QPixmap);
    bool isSaved();
    void setSaved(bool);
    bool isModified();
    void setModified(bool);

    QStack<GAction *> *undoList;
    QStack<GAction *> *redoList;

private:

    bool saved,
         modified;
};

#endif // GPIXMAP_H
