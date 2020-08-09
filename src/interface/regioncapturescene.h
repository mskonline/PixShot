#ifndef REGIONCAPTURESCENE_H
#define REGIONCAPTURESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPixmap>

#include "../graphics/items/regionselect.h"

class RegionCaptureScene : public QGraphicsScene
{
    Q_OBJECT
private:

    RegionSelect *item;
    QGraphicsPixmapItem *pixItem;
public:

    QPixmap regionPix;
    RegionCaptureScene(QPixmap pix);
    ~RegionCaptureScene();
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *keyEvent);
signals:

    void closeView();
public slots:

    void captureRegion();
};

#endif // REGIONCAPTURESCENE_H
