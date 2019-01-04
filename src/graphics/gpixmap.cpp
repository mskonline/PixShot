#include "gpixmap.h"

GPixMap::GPixMap(QPixmap p) :
    QGraphicsPixmapItem(p)
{
    this->notifiedChange = false;
    this->saved = true;
    this->modified = false;
    this->zoomStep = 1;
    this->scale = 1;

    undoList = new QStack<GAction *>();
    redoList = new QStack<GAction *>();
}

bool GPixMap::isSaved()
{
    return saved;
}

void GPixMap::setSaved(bool d)
{
    saved = d;
}

bool GPixMap::isModified()
{
    return this->modified;
}

void GPixMap::setModified(bool m)
{
    this->modified = m;
}
