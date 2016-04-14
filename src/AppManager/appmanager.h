#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QClipboard>

#include "../Interface/interface.h"
#include "../Preferences/preferences.h"
#include "../Commons/commons.h"

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

    void createInterface();
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
