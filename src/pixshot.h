#ifndef PIXSHOT_H
#define PIXSHOT_H

#include <QApplication>

#include "./interface/interface.h"
#include "./preferences/preferences.h"

#if defined (Q_OS_WIN)
#include <windows.h>
#endif

/**
 * @brief The main application class
 * @author Sai Kumar Manakan
 * @date 2020
 * @copyright GPL 2.0
 */
class PixShot: public QApplication
{
    Q_OBJECT
public:
    explicit PixShot(int argc, char *argv[]);
    ~PixShot();
    void init();

private:
    Interface *pixShotInterface;
    Preferences *preferences;

    void loadInterface();
    void loadModules();
    void close();
    void setConnections();
    void checkClipboardforImages();

    #ifdef _WIN32
    bool winEventFilter(MSG * msg, long * result);
    #endif

public slots:
    void closeApp();
    void copyToClipBoard();
    void copyFromClipBoard();
    void updatePreferences(int);
};

#endif // QAPP_H
