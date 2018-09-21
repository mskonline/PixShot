#ifndef QAPP_H
#define QAPP_H

#include <QApplication>
#if defined (Q_OS_WIN)
#include <windows.h>
#endif

class QApp : public QApplication
{
    Q_OBJECT
public:

    explicit QApp(int argc, char *argv[]);
    ~QApp();
    #ifdef _WIN32
    bool winEventFilter(MSG * msg, long * result);
    #endif
signals:

    void activateRegionCapture();
};

#endif // QAPP_H
