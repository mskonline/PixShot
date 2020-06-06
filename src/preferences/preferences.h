#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "../interface/preferenceinterface.h"
#include <QSettings>

/**
 * @brief The Preferences class
 * @details This class is responsible for saving and retrieving the application preferences / settings
 * @author Sai Kumar Manakan
 * @date 2011 - 2020
 * @copyright GPL 2.0
 */
class Preferences: public QSettings
{
    Q_OBJECT

public:

    // Properties accessible to AppManager
    QColor itemColor;
    QColor interfaceBGColor;
    QString saveLocation;
    bool toPreferedLocation;
    QString lastSaveLocation;
    QString imageFormat;
    QString lastOpenLocation;
    QFont textItemFont;

    bool toTrayOnClose;
    bool trayIcon;
    bool trayOnStart;
    bool updateOnStart;

    // Functions
    Preferences(QString, Format format = QSettings::IniFormat, QObject *parent = 0);
    ~Preferences();

    void load();
    void showPreferences(QWidget *parent = 0);
    void getPreference(int);
    static QVariant fetchProperty(QString, QString);
    static void createDefault(QString);

private:

    PreferenceInterface *prefUi;

public slots:

    void cancelPreferences();
    void savePreferences(int);

signals :

    void updatePreferences(int);
};

#endif // PREFERENCES_H
