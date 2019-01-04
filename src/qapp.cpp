#include "qapp.h"

QApp::QApp(int argc, char *argv[]): QApplication(argc,argv)
{
    // do nothing
}

#if defined (Q_OS_WIN)
bool QApp::winEventFilter(MSG * msg, long * result)
{
    switch(msg->message)
    {
        case WM_HOTKEY:
            emit activateRegionCapture();
            break;
    }

    return(false);
}
#endif

QApp::~QApp()
{
}
