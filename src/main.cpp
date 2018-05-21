#include "appmanager/appmanager.h"
#include "commons/commons.h"
#include "qapp.h"
#include <QSharedMemory>


int main(int argc, char *argv[])
{

    QApp *application = new QApp(argc, argv);
    application->setStyleSheet(APP_STYLE);
    application->addLibraryPath(LIB_PATH);

    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setOrganizationDomain(APP_WEBSITE);

    AppManager *app;

    app = new AppManager();
    app->init();

    QObject::connect(application,SIGNAL(activateRegionCapture()),app,SLOT(activateRegionCapture()));

    if(application->exec() == NORMAL_RUN)
    {
        delete app;
        return NORMAL_RUN;
    }
    else
        return -1;
}
