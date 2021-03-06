#include "crop.h"
#include <QPainter>
#include <QPushButton>

Crop::Crop(QGraphicsScene *scene, QGraphicsItem *parent)
{
    this->setParentItem(parent);
    this->setPos(0,0);

    cropStartPoint.setX(0);
    cropStartPoint.setY(0);
    cropEndPoint = parent->boundingRect().bottomRight();

    this->setOpacity(0.5);
    this->setZValue(parent->zValue() + 1);

    pen.setColor(QColor(Qt::gray));
    pen.setStyle(Qt::NoPen);
    selectionPen.setStyle(Qt::DashLine);

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(Qt::gray));
    selectionBrush.setStyle(Qt::NoBrush);

    pixTop.setX(0);
    pixTop.setY(0);

    this->scene = scene;
    this->createTool();

    temp = "test";
}

void Crop::setOptions(ItemProperties *prop)
{
    /* IGNORE
    this->pen = prop->itemPen;
    this->brush = prop->itemBrush;
    */
}

QRectF Crop::boundingRect() const
{
    return QRectF(cropStartPoint, cropEndPoint);
}

void Crop::createTool()
{
    QPushButton *pb_crop;
    QPushButton *pb_cancel;

    Form = new QWidget;
    Form->resize(174, 40);
    Form->setMinimumSize(QSize(174, 40));
    Form->setMaximumSize(QSize(174, 40));
    Form->setStyleSheet(QString::fromUtf8("QWidget {background-color: rgb(170, 170, 170);}\n"
        "QPushButton{background-color:none;}"));

    pb_crop = new QPushButton(Form);
    pb_crop->setText("Crop");
    pb_crop->setGeometry(QRect(10, 10, 75, 23));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/images/crop.png"), QSize(), QIcon::Normal, QIcon::Off);
    pb_crop->setIcon(icon);
    pb_crop->setIconSize(QSize(14, 16));
    pb_cancel = new QPushButton(Form);
    pb_cancel->setText("Cancel");
    pb_cancel->setGeometry(QRect(91, 10, 75, 23));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/images/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
    pb_cancel->setIcon(icon1);
    pb_cancel->setIconSize(QSize(14, 16));

    connect(pb_crop, SIGNAL(pressed()), this, SLOT(emitCrop()));
    connect(pb_cancel, SIGNAL(pressed()), this, SLOT(emitCancel()));

    panel = scene->addWidget(Form);
    panel->setPos(cropEndPoint);
    panel->setZValue(this->zValue() + 10);
}

void Crop::emitCancel()
{
    emit cancel();
}

void Crop::emitCrop()
{
    emit crop();
}

void Crop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF(spoint,epoint).normalized());*/
    painter->setPen(pen);
    painter->setBrush(brush);

    /*
     * The FourRect grey out
     * In order to provide an impression of the crop area highlighted
     * and the rest of the area greyed out, we draw four RectF around
     * the crop area
     *
     * 1 RectF - top of the crop area
     * 2 RectFs - on the sides
     * 1 RectF - bottom of the crop area
     */

    // Rect 1
    QPointF p2(cropEndPoint.x(), startPoint.y());
    painter->drawRect(QRectF(pixTop, p2).normalized());

    // Rect 2
    QPointF p3(0, startPoint.y());
    QPointF p4(startPoint.x(), endPoint.y());
    painter->drawRect(QRectF(p3, p4).normalized());

    // Rect 3
    QPointF p5(endPoint.x(), startPoint.y());
    QPointF p6(cropEndPoint.x(), endPoint.y());
    painter->drawRect(QRectF(p5, p6).normalized());

    // Rect 4
    QPointF p7(0, endPoint.y());
    painter->drawRect(QRectF(p7, cropEndPoint).normalized());

    // Draw selection Rect
    painter->setPen(selectionPen);
    painter->setBrush(selectionBrush);
    painter->drawRect(QRectF(startPoint, endPoint).normalized());

    panel->setPos(endPoint);
}

Crop::~Crop()
{    
}
