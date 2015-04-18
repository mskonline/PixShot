#include "qapp.h"

QApp::QApp(int argc, char *argv[]): QApplication(argc,argv)
{
}

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

QApp::~QApp()
{
}
