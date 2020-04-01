#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QClipboard>

#include "../interface/interface.h"
#include "../preferences/preferences.h"
#include "../commons/commons.h"

/**
 * @brief The AppManager class
 */
class AppManager: public QObject
{
    Q_OBJECT

public:

    AppManager();
    ~AppManager();
    void init();

private:

    Interface *interface;
    Preferences *preferences;

    void loadInterface();
    void loadModules();
    void close();
    void setConnections();
    void checkClipboardforImages();

public slots:

    void closeApp();
    void activateRegionCapture();
    void copyToClipBoard();
    void copyFromClipBoard();
    void updatePreferences(int);
};

#endif // APPMANAGER_H
