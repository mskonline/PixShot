#ifndef QAPP_H
#define QAPP_H

#include <QApplication>
#include <windows.h>

class QApp : public QApplication
{
    Q_OBJECT
public:

    explicit QApp(int argc, char *argv[]);
    ~QApp();
    bool winEventFilter(MSG * msg, long * result);

signals:

    void activateRegionCapture();
};

#endif // QAPP_H
