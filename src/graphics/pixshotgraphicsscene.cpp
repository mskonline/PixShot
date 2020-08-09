#include "pixshotgraphicsscene.h"
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

PixShotGraphicsScene::PixShotGraphicsScene(ItemProperties *itemProperties)
{
    // Initialize
    this->DRAW_MODE = false;
    this->OBJECT_TYPE = RECTANGLE;
    this->prop = itemProperties;
    this->item = nullptr;
    this->currentPix = nullptr;
    this->selectionMode = false;

    pixList = new QList<GPixMap *>;
}

/**
 * The mouse press event. Every item is rendered based on the selection state
 *
 * @brief PixShotGraphicsScene::mousePressEvent
 * @param event
 */
void PixShotGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && this->DRAW_MODE)
    {
        currentPix->setModified(true);
        switch(this->OBJECT_TYPE)
        {
        case POINTER:
            // do nothing
            break;
        case RECTANGLE:
            item = new Rectangle(currentPix);
            break;
        case CIRCLE:
            item = new Circle(currentPix);
            break;
        case ARROW:
            item = new Arrow(currentPix);
            break;
        case TEXT:      //DRAW_MODE = false;
            textItem = new Text(currentPix);
            textItem->setPos(event->scenePos());
            textItem->setFont(prop->font);
            textItem->setDefaultTextColor(prop->fontColor);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(currentPix->zValue() + 100);
            connect(textItem,SIGNAL(lostFocus(TextItem *)),this,SLOT(TextItemFocusLost(TextItem*)));

            QGraphicsScene::mousePressEvent(event);
            return;
            break;
        case HIGHLIGHT:
            item = new HighLighter(currentPix);
            break;
        case CROP:
            item = new Crop(this,currentPix);
            Crop *t = dynamic_cast<Crop *> (item);
            connect(t, SIGNAL(crop()), this, SLOT(cropImage()));
            connect(t, SIGNAL(cancel()), this, SLOT(cancelCrop()));
            break;
        }

        item->setOptions(this->prop);
        item->setStartPoint(event->scenePos());
        item->setEndPoint(event->scenePos());

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

    if(this->items().size() > 0 && !this->DRAW_MODE)
    {
        QList<QGraphicsItem *> itemsList = this->selectedItems();
        QGraphicsItem *item;
        for(int i = 0; i < itemsList.size(); ++i)
        {
            item = itemsList.at(i);
            item->setData(0, item->pos());
        }
    }

    // Lets update the scene
    this->update();

    if(!selectionMode)
        event->accept();
    else
        QGraphicsScene::mousePressEvent(event);
}

void PixShotGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(!selectionMode)
    {
        event->accept();
    }
    else
    {
        QGraphicsScene::mouseDoubleClickEvent(event);
    }
}

void PixShotGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->DRAW_MODE)
    {
        /* One item at Once */
        if(this->OBJECT_TYPE == CROP){
            this->DRAW_MODE = false;
            this->update();

            QGraphicsScene::mouseReleaseEvent(event);
            emit resetCursor();
            return;
        }
    }

    QList<QGraphicsItem *> itemsList = this->selectedItems();
    QGraphicsItem *item;

    for(int i = 0; i < itemsList.size(); ++i)
    {
        item = itemsList.at(i);
        action = new GAction();
        action->item = item;
        action->action = MOVE;
        action->vt.setValue(item->data(0).value<QPointF>());
        this->currentPix->undoList->push(action);
    }

    this->update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void PixShotGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && this->DRAW_MODE)
    {
        // TODO : better impl
        if(this->OBJECT_TYPE == TEXT)
        {
            return;
        }

        item->setEndPoint(event->scenePos());
    }

    this->update();
    QGraphicsScene::mouseMoveEvent(event);
}

void PixShotGraphicsScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
    /* Keyboard events on the Scene */
    switch(keyEvent->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Return:

        if(this->OBJECT_TYPE == CROP)
        {
            this->cropImage();
        }

        break;
    case Qt::Key_Escape:
        this->DRAW_MODE = false;
        if(item)
        {
            if(this->OBJECT_TYPE == CROP)
            {
                Crop *t = dynamic_cast<Crop *> (item);
                this->removeItem(t->panel);
                this->removeItem(item);
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
        {
            item->hide();
        }

        break;
    case Qt::Key_Control:
        emit releaseCtrl();
        break;
    case Qt::Key_Z:
        if(keyEvent->modifiers() == Qt::ControlModifier)
        {
            this->undo();
        }
        break;
    case Qt::Key_Y:
        if(keyEvent->modifiers() == Qt::ControlModifier)
        {
            this->redo();
        }
        break;
    default:;
        /* Do Nothing */
    }

    this->update();
}

void PixShotGraphicsScene::setPixmap(QPixmap pixmap)
{
    QSize pixmapSize = pixmap.size();
    int scaledWidth = pixmapSize.width();
    int scaledHeight = pixmapSize.height();
    bool requiresScaling = false;
    QSize vSize = this->views().last()->size();

    if(pixmapSize.width() > vSize.width())
    {
        requiresScaling = true;
        scaledWidth = vSize.width();
    }

    if (pixmapSize.height() > vSize.height())
    {
        requiresScaling = true;
        scaledHeight = vSize.height();
    }

    if(currentPix)
    {
        currentPix->setVisible(false);
    }

    if(requiresScaling)
    {
        pixmap = pixmap.scaled(scaledWidth, scaledHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    currentPix = new GPixMap(pixmap);

    pixList->append(currentPix);
    this->addItem(currentPix);
}

void PixShotGraphicsScene::setActivePixmap(int index)
{
    if(currentPix)
    {
        currentPix->setVisible(false);
        currentPix = pixList->at(index);
        currentPix->setVisible(true);
        this->setSceneRect(currentPix->boundingRect());
    }
}

void PixShotGraphicsScene::removePixmap(int index)
{
    currentPix = pixList->at(index);

    // Empty stacks
    currentPix->undoList->clear();
    currentPix->redoList->clear();

    this->removeItem(currentPix);
    pixList->removeAt(index);

    // Last pixmap is removed
    if(pixList->count() == 0)
    {
        // Reset the SceneRect
        this->setSceneRect(QRect(0, 0, 1, 1));
        return;
    }

    index = index != 0 ? index - 1 : 0;

    currentPix = pixList->at(index);
    this->setSceneRect(currentPix->boundingRect());
    currentPix->setVisible(true);
}

void PixShotGraphicsScene::undo()
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

void PixShotGraphicsScene::redo()
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

void PixShotGraphicsScene::renderToFile(QString path)
{
    QImage *image = new QImage(this->sceneRect().size().toSize(), QImage::Format_RGB32);
    QPainter *painter = new QPainter(image);

    this->render(painter);

    painter->end();
    painter->save();

    image->save(path);

    currentPix->setSaved(true);
    currentPix->setModified(false);
    currentPix->notifiedChange = false;

    delete image;
    delete painter;
}

void PixShotGraphicsScene::renderToPrinter()
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

void PixShotGraphicsScene::TextItemFocusLost(Text *item)
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

void PixShotGraphicsScene::cropImage()
{
    action = new GAction();
    action->action = IMG_CROP;
    action->vt.setValue(currentPix->pixmap());
    currentPix->undoList->push(action);

    //Do Crop
    Crop *crop = dynamic_cast<Crop *> (item);
    QRect rectf = QRect(crop->getStartPoint().toPoint(), crop->getEndPoint().toPoint());

    QPixmap cropPic = currentPix->pixmap().copy(rectf);
    currentPix->setPixmap(cropPic);
    this->setSceneRect(currentPix->boundingRect());

    this->removeItem(crop->panel);
    this->removeItem(crop);

    if(crop)
    {
        delete crop;
    }

    emit resetCursor();

    this->currentPix->unsetCursor();
    this->update();
}

void PixShotGraphicsScene::cancelCrop()
{
    Crop *t = dynamic_cast<Crop *> (item);
    this->removeItem(t);
    this->removeItem(t->panel);

    this->DRAW_MODE = true;
}

bool PixShotGraphicsScene::checkForAllSaved()
{
    int pixCount = this->pixList->count();

    if(pixCount == 0)
    {
        return true;
    }

    GPixMap *pixmap;

    for(int i = 0; i < pixCount; ++i)
    {
        pixmap = this->pixList->at(i);

        if(pixmap->isSaved())
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void PixShotGraphicsScene::clearObjects()
{
    QList<QGraphicsItem *> itemsList = this->currentPix->childItems();
    int index;

    for(index = 0 ; index < itemsList.size() ; ++index)
    {
        itemList.at(index)->hide();
    }

    GAction *action = new GAction();
    action->action = DELETE_ALL;
    action->vt.setValue(index);

    this->currentPix->undoList->push(action);
}


void PixShotGraphicsScene::setTextItemFont(QFont font)
{
    this->textItemFont = font;
}

int PixShotGraphicsScene::pixmapCount()
{
    return pixList->size();
}

qreal PixShotGraphicsScene::getPixScale()
{
    if(currentPix)
    {
        return currentPix->scale;
    }
    else
    {// When opening the first pix
        return 1;
    }
}

void PixShotGraphicsScene::setPixScale(qreal s)
{
    if(currentPix)
    {
        currentPix->scale = s;
    }
}

int PixShotGraphicsScene::getZoomStep()
{
    if(currentPix)
    {
        return currentPix->zoomStep;
    }
    else
    {
        // When opening the first pix
        return 1;
    }
}

void PixShotGraphicsScene::setZoomStep(int zStep)
{
    if(currentPix)
    {
        currentPix->zoomStep = zStep;
    }
}

void PixShotGraphicsScene::setSelectionMode(bool m)
{
    this->selectionMode = m;
}

bool PixShotGraphicsScene::isModifed(int index)
{
    return pixList->at(index)->isModified();
}

PixShotGraphicsScene::~PixShotGraphicsScene()
{
    this->clear();
}
