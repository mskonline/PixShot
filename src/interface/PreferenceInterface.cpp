#include "PreferenceInterface.h"
#include "../commons/commons.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QKeyEvent>

PreferenceInterface::PreferenceInterface(QWidget *parent):
    QWidget(parent,Qt::Window | Qt::WindowCloseButtonHint)
{   
    this->setupUi(this);

    int h_by2 = this->height() / 2;
    int w_by2 = this->width() / 2;
    int p_midX = parent->x() + parent->width() / 2;
    int p_midY = parent->y() + parent->height() / 2;

    this->move(p_midX - w_by2, p_midY - h_by2) ;

    setAttribute(Qt::WA_QuitOnClose);
    setConnections();
}

void PreferenceInterface::setConnections()
{
    connect(this->pb_browse,SIGNAL(released()),this,SLOT(getLocation()));
    connect(this->rb_askMe,SIGNAL(clicked(bool)),this,SLOT(askSaveLocation(bool)));
    connect(this->rb_saveLocation,SIGNAL(clicked(bool)),this,SLOT(setSaveLocation(bool)));
    connect(this->cb_imgFormat,SIGNAL(currentIndexChanged(int)),this,SLOT(imageFormatChanged(int)));
    connect(this->pb_textItemFont,SIGNAL(released()),this,SLOT(setTextItemFont()));
    connect(this->pb_itemColor,SIGNAL(released()),this,SLOT(setItemColor()));
    connect(this->pb_interfaceColor,SIGNAL(released()),this,SLOT(setInterfaceColor()));

    connect(this->cb_toTray_onClose,SIGNAL(clicked(bool)),this,SLOT(setTrayOnClose(bool)));
    connect(this->cb_always_trayIcon,SIGNAL(clicked(bool)),this,SLOT(setTrayIcon(bool)));
    connect(this->cb_toTray_onStart,SIGNAL(clicked(bool)),this,SLOT(setTrayOnStart(bool)));
}

void PreferenceInterface::getLocation()
{
    QString location;
    location = QFileDialog::getExistingDirectory(this,"Select a Location",this->le_saveLocation->text());

    if(!location.isEmpty())
        le_saveLocation->setText(location + "/");

    emit savePreferences(SAVE_LOCATION);
}

void PreferenceInterface::askSaveLocation(bool v)
{
    emit savePreferences(SAVE_LOCATION);
}

void PreferenceInterface::setSaveLocation(bool v)
{
    if(v)
    {
        QString location;
        location = this->le_saveLocation->text();

        if(!location.isEmpty())
            emit savePreferences(SAVE_LOCATION);
    }
}

void PreferenceInterface::imageFormatChanged(int v)
{
    emit savePreferences(IMAGE_FORMAT);
}

void PreferenceInterface::setTextItemFont()
{
    bool chg;
    QFont f = QFontDialog::getFont(&chg,this->textItemFont,this,"Select a Font");

    if(chg)
    {
        this->textItemFont = f;
        this->pb_textItemFont->setText(f.family());
        emit savePreferences(TEXT_ITEM_FONT);
    }
}

void PreferenceInterface::setItemColor()
{
    this->itemColor = QColorDialog::getColor(QColor(Qt::black),this,"Select a Color");

    int w = this->pb_itemColor->width();
    int h = this->pb_itemColor->height();

    QPixmap p(w,h);
    p.fill(this->itemColor);
    QIcon i(p);
    this->pb_itemColor->setIcon(i);

    emit savePreferences(ITEM_COLOR);
}

void PreferenceInterface::setInterfaceColor()
{
    this->interfaceBGColor = QColorDialog::getColor(QColor(Qt::black),this,"Select a Color");
    int w = this->pb_interfaceColor->width();
    int h = this->pb_interfaceColor->height();

    QPixmap p(w,h);
    p.fill(this->interfaceBGColor);
    QIcon i(p);
    this->pb_interfaceColor->setIcon(i);

    emit savePreferences(INTERFACE_BG_COLOR);
}

void PreferenceInterface::setTrayOnClose(bool v)
{
    this->toTrayOnClose = v;
    emit savePreferences(TO_TRAY_ONCLOSE);
}

void PreferenceInterface::setTrayIcon(bool v)
{
    this->trayIcon = v;

    this->cb_toTray_onClose->setDisabled(!v);
    this->cb_toTray_onStart->setDisabled(!v);

    if(!v) {
        this->cb_toTray_onStart->setChecked(!v);
        this->cb_toTray_onClose->setChecked(!v);

        this->setTrayOnStart(false);
        this->setTrayOnClose(false);
    }

    emit savePreferences(TOGGLE_TRAY_ICON);
}

void PreferenceInterface::setTrayOnStart(bool v)
{
    this->trayOnStart = v;
    emit savePreferences(TO_TRAY_ON_START);
}

void PreferenceInterface::setUpdateOnStart(bool v)
{
    this->updateOnStart = v;
    emit savePreferences(UPDATE_ON_START);
}

void PreferenceInterface::keyReleaseEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
         case Qt::Key_Escape:
         case Qt::Key_Delete:
            this->close();
            break;
    }
}
