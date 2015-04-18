#include "gscene.h"
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPushButton>
#include <QLabel>
#include <QStack>
#include <QVariant>
#include <QTextCursor>
#include <QGraphicsView>
#include <QGraphicsTextItem>

GScene::GScene(ItemProperties *prop)
{
    DRAW_MODE = false;
    this->OBJECT_TYPE = RECTANGLE;
    this->prop = prop;
    this->item = NULL;
    this->currentPix = NULL;
    this->selectionMode = false;

    pixList = new QList<GPixMap *>;
}

void GScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && DRAW_MODE)
    {
        currentPix->setModified(true);
        switch(this->OBJECT_TYPE)
        {
            case RECTANGLE: item = new RectItem(currentPix);
                    break;
            case CIRCLE:    item = new CircleItem(currentPix);
                    break;
            case ARROW:     item = new ArrowItem(currentPix);
                    break;
            case TEXT:      //DRAW_MODE = false;
                            textItem = new TextItem(currentPix);
                            textItem->setPos(event->scenePos());
                            textItem->setFont(prop->font);
                            textItem->setDefaultTextColor(prop->fontColor);
                            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
                            textItem->setZValue(currentPix->zValue() + 100);
                            connect(textItem,SIGNAL(lostFocus(TextItem *)),this,SLOT(TextItemFocusLost(TextItem*)));

                            QGraphicsScene::mousePressEvent(event);
                            return;
                    break;
            case HIGHLIGHT: item = new HighLighterItem(currentPix);
                    break;
            case CROP:      item = new CropItem(this,currentPix);
                            CropItem *t = dynamic_cast<CropItem *> (item);
                            connect(t,SIGNAL(crop()),this,SLOT(cropImage()));
                            connect(t,SIGNAL(cancel()),this,SLOT(cancelCrop()));
        }

        item->setOptions(this->prop);
        item->spoint = event->scenePos();
        item->epoint = event->scenePos();

        if(this->OBJECT_TYPE != CROP)
        {
            action = new GAction();
            action->item = item;
            action->action = CREATE;
            action->vt.setValue(item->pos());
            this->currentPix->undoList->push(action);
        }

        if(currentPix->isSaved()) {
            emit pixmapEdited(true);
            currentPix->setSaved(false);
        }
    }

    if(this->items().size() > 0 && !DRAW_MODE)
    {
        QList<QGraphicsItem *> itmList = this->selectedItems();
        QGraphicsItem *item;
        for(int i = 0; i < itmList.size(); ++i)
        {
            item = itmList.at(i);
            item->setData(0,item->pos());
        }
    }

    this->update();

    if(!selectionMode)
        event->accept();
    else
        QGraphicsScene::mousePressEvent(event);
}

void GScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(!selectionMode)
        event->accept();
    else
        QGraphicsScene::mouseDoubleClickEvent(event);
}

void GScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(DRAW_MODE)
    {
        /* One item at Once */
        if(this->OBJECT_TYPE == CROP)
            DRAW_MODE = false;
    }

    QList<QGraphicsItem *> itmList = this->selectedItems();
    QGraphicsItem *item;

    for(int i = 0; i < itmList.size(); ++i)
    {
        item = itmList.at(i);
        action = new GAction();
        action->item = item;
        action->action = MOVE;
        action->vt.setValue(item->data(0).value<QPointF>());
        this->currentPix->undoList->push(action);
    }

    this->update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void GScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && DRAW_MODE)
    {
        // TODO : better impl
        if(this->OBJECT_TYPE == TEXT)
            return;

        item->epoint = event->scenePos();
    }

    this->update();
    QGraphicsScene::mouseMoveEvent(event);
}

void GScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
    /* Keyboard events on the Scene */
    switch(keyEvent->key())
    {
        case Qt::Key_Enter:
        case Qt::Key_Return:

            if(this->OBJECT_TYPE == CROP)
                this->cropImage();

            break;
        case Qt::Key_Escape:
            this->DRAW_MODE = false;
            if(item)
            {
                this->removeItem(item);
                if(this->OBJECT_TYPE == CROP)
                {
                    CropItem *t = dynamic_cast<CropItem *> (item);
                    this->removeItem(t->panel);
                }
            }
            emit resetCursor();
            break;
        case Qt::Key_Delete:
            // Delete an item which has focus/selected
            this->DRAW_MODE = false;
            action = new GAction();
            action->action = DELETE;
            action->vt.setValue(this->selectedItems());
            currentPix->undoList->push(action);

            foreach(QGraphicsItem *item, this->selectedItems())
                item->hide();

            break;
        case Qt::Key_Control:
            emit releaseCtrl();
            break;
        case Qt::Key_Z:
            if(keyEvent->modifiers() && Qt::ControlModifier){
                this->undo();
            }
            break;
        case Qt::Key_Y:
            if(keyEvent->modifiers() && Qt::ControlModifier){
                this->redo();
            }
            break;
        default:;
            /* Do Nothing */
    }

    this->update();
}

void GScene::setPixmap(QPixmap p)
{
    if(currentPix)
        currentPix->setVisible(false);

    currentPix = new GPixMap(p);
    pixList->append(currentPix);

    this->addItem(currentPix);
    this->setSceneRect(currentPix->boundingRect());
}

void GScene::setActivePixmap(int i)
{
    if(currentPix)
    {
        currentPix->setVisible(false);
        currentPix = pixList->at(i);
        currentPix->setVisible(true);
        this->setSceneRect(currentPix->boundingRect());
    }
}

void GScene::removePixmap(int index)
{
    currentPix = pixList->at(index);

    // Empty stacks
    currentPix->undoList->clear();
    currentPix->redoList->clear();

    this->removeItem(currentPix);
    pixList->removeAt(index);

    // Last pixmap is removed
    if(pixList->count() == 0) {
        // Reset the SceneRect
        this->setSceneRect(QRect(0,0,1,1));
        return;
    }

    index = index != 0 ? index - 1 : 0;

    currentPix = pixList->at(index);
    this->setSceneRect(currentPix->boundingRect());
    currentPix->setVisible(true);
}

void GScene::undo()
{
    if(!currentPix->undoList->isEmpty())
    {
        GAction *gAction = currentPix->undoList->pop();

        QGraphicsItem *item = gAction->item;
        QVariant vt;
        int i;

        switch(gAction->action)
        {
            case CREATE:
                item->hide();
                break;
            case DELETE:
                itemList = gAction->vt.value<QList <QGraphicsItem*> >();
                foreach(QGraphicsItem *i, itemList)
                    i->show();
                break;
            case DELETE_ALL:
                itemList = currentPix->childItems();
                for(i = 0; i < gAction->vt.toInt(); ++i)
                    itemList.at(i)->show();
                break;
            case MOVE:
                vt.setValue(item->pos());
                item->setPos(gAction->vt.value<QPointF>());
                gAction->vt = vt;
                break;
            case IMG_CROP:
                vt.setValue(currentPix->pixmap());
                currentPix->setPixmap(gAction->vt.value<QPixmap>());
                this->setSceneRect(currentPix->boundingRect());
                gAction->vt = vt;
                break;
        }

        currentPix->redoList->push(gAction);

        if(currentPix->undoList->size() == 0)
        {
            emit pixmapEdited(true);
            currentPix->notifiedChange = true;
            currentPix->setModified(false);
        }
    }

    this->update();
}

void GScene::redo()
{
    if(!currentPix->redoList->isEmpty())
    {
        GAction *gAction = currentPix->redoList->pop();

        QGraphicsItem *item = gAction->item;
        QVariant vt;
        int i;

        switch(gAction->action)
        {
            case CREATE:
                item->show();
                break;
            case DELETE:
                itemList = gAction->vt.value<QList <QGraphicsItem*> >();
                foreach(QGraphicsItem *item, itemList)
                    item->hide();
                break;
            case DELETE_ALL:
                itemList = currentPix->childItems();
                for(i = 0; i < gAction->vt.toInt(); ++i)
                    itemList.at(i)->hide();
                break;
            case MOVE:
                vt.setValue(item->pos());
                item->setPos(gAction->vt.value<QPointF>());
                gAction->vt = vt;
                break;
            case IMG_CROP:
                vt.setValue(currentPix->pixmap());
                currentPix->setPixmap(gAction->vt.value<QPixmap>());
                this->setSceneRect(currentPix->boundingRect());
                gAction->vt = vt;
                break;
        }

        currentPix->undoList->push(gAction);

        if(currentPix->redoList->size() == 0)
        {
            emit pixmapEdited(true);
            currentPix->notifiedChange = true;
            currentPix->setModified(false);
        }
    }

    this->update();
}

void GScene::renderToFile(QString path)
{
    QImage *img = new QImage(this->sceneRect().size().toSize(),
                             QImage::Format_RGB32);
    QPainter *painter = new QPainter(img);

    this->render(painter);

    painter->end();
    painter->save();

    img->save(path);

    currentPix->setSaved(true);
    currentPix->setModified(false);
    currentPix->notifiedChange = false;

    delete img;
    delete painter;
}

void GScene::renderToPrinter()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);

    QPrintDialog pDialog(printer);

    if(pDialog.exec() == QDialog::Accepted)
    {
        QPainter *painter = new QPainter(printer);

        this->render(painter);
        painter->end();
        delete painter;
    }
}

void GScene::TextItemFocusLost(TextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if(item->toPlainText().isEmpty())
    {
        this->removeItem(item);
        item->deleteLater();
    }
}

void GScene::cropImage()
{
    action = new GAction();
    action->action = IMG_CROP;
    action->vt.setValue(currentPix->pixmap());
    currentPix->undoList->push(action);

     //Do Crop
    CropItem *t = dynamic_cast<CropItem *> (item);
    QRect rectf = QRect(t->spoint.toPoint(),t->epoint.toPoint());

    QPixmap cropPic = currentPix->pixmap().copy(rectf);
    currentPix->setPixmap(cropPic);
    this->setSceneRect(currentPix->boundingRect());

    this->removeItem(t->panel);
    this->removeItem(t);

    if(t)
        delete t;

    emit resetCursor();

    this->currentPix->unsetCursor();
    this->update();
}

void GScene::cancelCrop()
{
    CropItem *t = dynamic_cast<CropItem *> (item);
    this->removeItem(t);
    this->removeItem(t->panel);

    DRAW_MODE = true;
}

bool GScene::checkForAllSaved()
{
    int pixCount = this->pixList->count();

    if(pixCount == 0)
      return true;

    GPixMap *p;

    for(int i = 0; i < pixCount; ++i)
    {
        p = this->pixList->at(i);

        if(p->isSaved())
            continue;
        else
            return false;
    }

    return true;
}

void GScene::clearObjects()
{
    QList<QGraphicsItem *> itemList = this->currentPix->childItems();
    int index;
    for(index = 0 ; index < itemList.size() ; ++index)
        itemList.at(index)->hide();

    GAction *a = new GAction();
    a->action = DELETE_ALL;
    a->vt.setValue(index);

    this->currentPix->undoList->push(a);
}


void GScene::setTextItemFont(QFont font)
{
    this->textItemFont = font;
}

int GScene::pixmapCount()
{
    return pixList->size();
}

qreal GScene::getPixScale()
{
    if(currentPix)
        return currentPix->scale;
    else // When opening the first pix
        return 1;
}

void GScene::setPixScale(qreal s)
{
    if(currentPix)
        currentPix->scale = s;
}

int GScene::getZoomStep()
{
    if(currentPix)
        return currentPix->zoomStep;
    else // When opening the first pix
        return 1;
}

void GScene::setZoomStep(int zStep)
{
    if(currentPix)
        currentPix->zoomStep = zStep;
}

void GScene::setSelectionMode(bool m)
{
    this->selectionMode = m;
}

bool GScene::isModifed(int index)
{
    return pixList->at(index)->isModified();
}

GScene::~GScene()
{
    this->clear();
}
