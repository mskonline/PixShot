#include "itemsettings.h"
#include <QPainter>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>

ItemSettings::ItemSettings(ItemProperties *prop,QWidget *parent):QWidget(parent,Qt::Tool)
{
    setupUi(this);

    this->prop = prop;

    this->fontColor = prop->fontColor;
    this->penColor = prop->itemPen.color();
    this->brushColor = prop->itemBrush.color();

    QPixmap penColor(45,11);
    penColor.fill(prop->itemPen.color());
    QIcon penIcon(penColor);
    this->pb_penColor->setIcon(penIcon);
    this->pb_penColor->setIconSize(QSize(45,11));
    this->sd_penWidth->setValue(prop->itemPen.width());
    this->cb_penStyle->setCurrentIndex(this->prop->itemPen.style() - 1);

    QPixmap brushColor(45,11);
    brushColor.fill(prop->itemBrush.color());
    QIcon brushIcon(brushColor);
    this->pb_brushColor->setIcon(brushIcon);
    this->pb_brushColor->setIconSize(QSize(45,11));
    this->cb_brushStyle->setCurrentIndex(this->prop->itemBrush.style());

    QPixmap fontColor(45,11);
    fontColor.fill(prop->fontColor);
    QIcon fontIcon(fontColor);
    this->pb_fontColor->setIcon(fontIcon);
    this->pb_fontColor->setIconSize(QSize(45,11));

    connect(pb_penColor,SIGNAL(released()),this,SLOT(setPenColor()));
    connect(pb_brushColor,SIGNAL(released()),this,SLOT(setBrushColor()));
    connect(pb_done,SIGNAL(released()),this,SLOT(saveSettings()));
    connect(pb_selectFont,SIGNAL(released()),this,SLOT(selectFont()));
    connect(pb_fontColor,SIGNAL(released()),this,SLOT(setFontColor()));

    int p_midX = parent->x() + 100;
    int p_midY = parent->y() + 150;

    this->move(p_midX , p_midY) ;

    this->activateWindow();
}

void ItemSettings::setPenColor()
{
    penColor = QColorDialog::getColor(QColor(Qt::black),this,"Select a Color");

    QPixmap p(45,11);
    p.fill(penColor);
    QIcon i(p);
    this->pb_penColor->setIcon(i);
    this->pb_penColor->setIconSize(QSize(45,11));
}

void ItemSettings::setBrushColor()
{
    brushColor = QColorDialog::getColor(QColor(Qt::black),this,"Select a Color");

    QPixmap p(45,11);
    p.fill(brushColor);
    QIcon i(p);
    this->pb_brushColor->setIcon(i);
    this->pb_brushColor->setIconSize(QSize(45,11));
}

void ItemSettings::setFontColor()
{
    fontColor = QColorDialog::getColor(QColor(Qt::black),this,"Select a Color");

    QPixmap p(45,11);
    p.fill(fontColor);
    QIcon i(p);
    this->pb_fontColor->setIcon(i);
    this->pb_fontColor->setIconSize(QSize(45,11));
}

void ItemSettings::saveSettings()
{
    QPen pen;
    pen.setColor(penColor);
    pen.setWidth(sd_penWidth->value());
    Qt::PenStyle ps = Qt::PenStyle(cb_penStyle->currentIndex() + 1);
    pen.setStyle(ps);

    QBrush brush;
    Qt::BrushStyle bs = Qt::BrushStyle(cb_brushStyle->currentIndex());
    brush.setStyle(bs);
    brush.setColor(brushColor);

    prop->setProperties(penColor,pen,brush,fontColor);
    this->close();
}

void ItemSettings::selectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this->prop->font,this);

    if(ok){
        this->prop->font = font;
    }
}

ItemSettings::~ItemSettings()
{
}
