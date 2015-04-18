#ifndef PREFERENCEINTERFACE_H
#define PREFERENCEINTERFACE_H

#include <QWidget>
#include "ui_preferences.h"

namespace Ui {
    class Preferences;
}

class PreferenceInterface:public QWidget, public Ui::Preferences
{
    Q_OBJECT

public :

    PreferenceInterface(QWidget *parent);
    QFont textItemFont;
    QColor itemColor;
    QColor interfaceBGColor;

    bool toTrayOnClose;
    bool trayIcon;
    bool trayOnStart;
    bool updateOnStart;

private :

    void setConnections();

protected :

    void keyReleaseEvent(QKeyEvent *);

public slots:

    void getLocation();
    void askSaveLocation(bool);
    void setSaveLocation(bool);
    void imageFormatChanged(int);
    void setTextItemFont();
    void setItemColor();
    void setInterfaceColor();
    void setTrayOnClose(bool);
    void setTrayIcon(bool);
    void setTrayOnStart(bool);
    void setUpdateOnStart(bool);

signals:

    void savePreferences(int);
};

#endif // PREFERENCEINTERFACE_H
