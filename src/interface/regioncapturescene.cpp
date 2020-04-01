#include "regioncapturescene.h"
#include <QTimer>

RegionCaptureScene::RegionCaptureScene(QPixmap pix)
{
    pixItem = new QGraphicsPixmapItem(pix);
    this->addItem(pixItem);
    this->item = nullptr;
}

void RegionCaptureScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        item = new RegionSelectItem(pixItem);
        item->spoint = item->epoint = event->scenePos();
        item->update();
        this->update();
    }
    else
        QGraphicsScene::mousePressEvent(event);
}

void RegionCaptureScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    this->update();

    // lets delay
    QTimer::singleShot(500,this,SLOT(captureRegion()));
}

void RegionCaptureScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        item->epoint = event->scenePos();
        this->update();
    }
    else
    {
        this->update();
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void RegionCaptureScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            if(item)
                this->removeItem(item);
            emit closeView();
        break;
    }
}

void RegionCaptureScene::captureRegion()
{
    const QRectF region = item->boundingRect();

    regionPix = pixItem->pixmap().copy(region.toRect());
    emit closeView();
}

RegionCaptureScene::~RegionCaptureScene()
{
    delete item;
    delete pixItem;
}

