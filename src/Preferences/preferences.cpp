#include "preferences.h"
#include "../Commons/commons.h"
#include <QDate>
#include <QDebug>

Preferences::Preferences(QString filename, Format format, QObject *parent)
    :QSettings(filename,format,parent)
{
}

void Preferences::load()
{
    beginGroup("SaveLocation");
    this->saveLocation = value("location").toString();
    this->toPreferedLocation = value("to_pref_location").toBool();
    endGroup();

    beginGroup("Work");
    this->lastSaveLocation = value("lastSaveLocation").toString();
    this->lastOpenLocation = value("lastOpenLocation").toString();
    this->imageFormat = value("imageFormat").toString();
    this->itemColor = QColor(value("itemColor").toString());
    this->interfaceBGColor = QColor(value("interfaceBGColor").toString());
    this->toTrayOnClose = value("toTrayOnClose").toBool();
    this->trayIcon = value("trayIcon").toBool();
    this->trayOnStart = value("trayOnStart").toBool();
    this->updateOnStart = value("updateOnStart").toBool();
    endGroup();
    sync();
}


// FIXME : static access ?
QVariant Preferences::fetchProperty(QString property,QString group)
{
    QSettings *settings = new QSettings(PREFERENCES_FILE,QSettings::IniFormat,NULL);
    settings->beginGroup(group);
    QVariant v = settings->value(property);
    settings->endGroup();

    return v;
}

void Preferences::showPreferences(QWidget *parent)
{
    prefUi = new PreferenceInterface(parent);

    //connect(prefUi->pb_cancel,SIGNAL(released()),this,SLOT(cancelPreferences()));
    //connect(prefUi->pb_save,SIGNAL(released()),this,SLOT(savePreferences()));
    connect(prefUi,SIGNAL(savePreferences(int)),this,SLOT(savePreferences(int)));

    // General Tab
    prefUi->le_saveLocation->setText(this->saveLocation);
    prefUi->rb_saveLocation->setChecked(this->toPreferedLocation);
    prefUi->rb_askMe->setChecked(!this->toPreferedLocation);

    // TODO : improve
    int index = prefUi->cb_imgFormat->findText(this->imageFormat.split(".")[1]);
    prefUi->cb_imgFormat->setCurrentIndex(index);

    // Style Tab
    prefUi->pb_textItemFont->setFont(this->textItemFont);

    int w = prefUi->pb_itemColor->width();
    int h = prefUi->pb_itemColor->height();

    QPixmap itemClr(w,h);
    itemClr.fill(this->itemColor);
    QIcon itemClrIcon(itemClr);
    prefUi->pb_itemColor->setIcon(itemClrIcon);
    prefUi->pb_itemColor->setIconSize(QSize(w,h));

    QPixmap interfaceBGClr(w,h);
    interfaceBGClr.fill(this->interfaceBGColor);
    QIcon interfaceBGClrIcon(interfaceBGClr);
    prefUi->pb_interfaceColor->setIcon(interfaceBGClrIcon);
    prefUi->pb_interfaceColor->setIconSize(QSize(w,h));

    prefUi->cb_always_trayIcon->setChecked(this->trayIcon);
    prefUi->cb_toTray_onStart->setChecked(this->trayOnStart);
    prefUi->cb_toTray_onClose->setChecked(this->toTrayOnClose);

    if(!this->trayIcon) {
        prefUi->cb_toTray_onStart->setDisabled(true);
        prefUi->cb_toTray_onClose->setDisabled(true);
    }

    prefUi->show();
}

void Preferences::cancelPreferences()
{
    //TODO : disconnect
    prefUi->close();
    delete prefUi;
}

void Preferences::savePreferences(int pref)
{  
    switch(pref)
    {
        case SAVE_LOCATION:
            this->saveLocation = prefUi->le_saveLocation->text();
            beginGroup("SaveLocation");
            setValue("location",this->saveLocation);

            this->toPreferedLocation = prefUi->rb_saveLocation->isChecked();
            setValue("to_pref_location",this->toPreferedLocation);
            endGroup();
            break;

        case LOCATIONS:
            beginGroup("Work");
            setValue("lastOpenLocation",lastOpenLocation);
            setValue("lastSaveLocation",lastSaveLocation);
            endGroup();
            break;

        case IMAGE_FORMAT:
            this->imageFormat = "." + prefUi->cb_imgFormat->currentText();
            beginGroup("Work");
            setValue("imageFormat", this->imageFormat);
            endGroup();
            break;

        case TEXT_ITEM_FONT:
            beginGroup("Work");
            setValue("textItemFont", this->prefUi->textItemFont.toString());
            this->textItemFont = this->prefUi->textItemFont;
            endGroup();
            break;

        case ITEM_COLOR:
            beginGroup("Work");
            setValue("itemColor",this->prefUi->itemColor.name());
            endGroup();
            this->itemColor = prefUi->itemColor;
            emit updatePreferences(ITEM_COLOR);
            break;

        case INTERFACE_BG_COLOR:
            this->interfaceBGColor = prefUi->interfaceBGColor;
            beginGroup("Work");
            setValue("interfaceBGColor",this->interfaceBGColor.name());
            endGroup();

            emit updatePreferences(INTERFACE_BG_COLOR);
            break;

        case TO_TRAY_ONCLOSE:
            this->toTrayOnClose = prefUi->toTrayOnClose;

            beginGroup("Work");
            setValue("toTrayOnClose",this->toTrayOnClose);
            endGroup();
            break;

        case TOGGLE_TRAY_ICON:
            this->trayIcon = prefUi->trayIcon;
            beginGroup("Work");
            setValue("trayIcon",this->trayIcon);
            endGroup();

            emit updatePreferences(TOGGLE_TRAY_ICON);
            break;

        case TO_TRAY_ON_START:
            this->trayOnStart = prefUi->trayOnStart;
            beginGroup("Work");
            setValue("trayOnStart",this->trayOnStart);
            endGroup();
            break;

        case UPDATE_ON_START:
            this->updateOnStart = prefUi->updateOnStart;
            beginGroup("Work");
            setValue("updateOnStart",this->updateOnStart);
            endGroup();
            break;
    }

    // write to .ini file
    sync();
}

void Preferences::createDefault(QString filename)
{
    QSettings settings(filename,QSettings::IniFormat,NULL);

    settings.beginGroup("PixShot");
    settings.setValue("version",VERSION);
    settings.setValue("firstrun",QDate::currentDate());
    settings.endGroup();
    settings.beginGroup("SaveLocation");
    settings.setValue("location","./");
    settings.setValue("to_pref_location",false);
    settings.endGroup();

    settings.beginGroup("Work");
    settings.setValue("lastOpenLocation", "./");
    settings.setValue("lastSaveLocation","./");
    settings.setValue("imageFormat",".png");
    settings.setValue("itemColor","#FF3300");
    settings.setValue("interfaceBGColor","#808080");
    settings.setValue("toTrayOnClose",true);
    settings.setValue("trayIcon",true);
    settings.setValue("trayOnStart",true);
    settings.setValue("updateOnStart",false);
    settings.endGroup();
    settings.sync();
}

Preferences::~Preferences()
{
    sync();
}

