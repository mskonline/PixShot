#ifndef GSCENE_H
#define GSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QList>
#include <QMetaType>
#include "gpixmap.h"
#include "items/baseitem.h"
#include "items/rectitem.h"
#include "items/circleitem.h"
#include "items/arrowitem.h"
#include "items/textitem.h"
#include "items/cropitem.h"
#include "items/highlighteritem.h"
#include "../commons/commons.h"

class GScene : public QGraphicsScene
{
    Q_OBJECT

public:

    bool DRAW_MODE;
    OBJECTS OBJECT_TYPE;

    GScene(ItemProperties *);
    ~GScene();

    void setPixmap(QPixmap);
    void setNewScreen();
    void renderToFile(QString);
    void renderToPrinter();
    void removePixmap(int);
    bool checkForAllSaved();
    void setTextItemFont(QFont);
    int pixmapCount();
    qreal getPixScale();
    void setPixScale(qreal);
    void setZoomStep(int);
    int getZoomStep();
    void setSelectionMode(bool);
    bool isModifed(int);

private:

    BaseItem *item;
    ItemProperties *prop;
    QFont textItemFont;
    QGraphicsTextItem *textItem;
    GPixMap *currentPix;
    QList<GPixMap *> *pixList;
    QList<QGraphicsItem *> itemList;
    GAction *action;
    bool selectionMode;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *);

signals:

    void resetCursor();
    void pixmapEdited(bool);
    void releaseCtrl();

public slots:

    void undo();
    void redo();
    void cropImage();
    void cancelCrop();
    void clearObjects();
    void TextItemFocusLost(TextItem *);
    void setActivePixmap(int);
};

//int id = qRegisterMetaType<QList <QGraphicsItem *> >("QList <QGraphicsItem *>");
Q_DECLARE_METATYPE(QList <QGraphicsItem *>)
#endif // GSCENE_H
