#include "pixshot.h"
#include "./commons/commons.h"
#include "./constants/application.h"
#include "./constants/preference.h"

#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QMessageBox>
#include <QClipboard>

PixShot::PixShot(int argc, char *argv[]): QApplication(argc,argv)
{
    this->setStyleSheet(APP_STYLE);
    this->addLibraryPath(LIB_PATH);

    this->setApplicationName(APP_NAME);
    this->setApplicationVersion(APP_VERSION);
    this->setOrganizationName(APP_NAME);
    this->setOrganizationDomain(APP_WEBSITE);
}

/**
 * Init method to intialize the modules, interface and the connections
 *
 * @brief AppManager::init
 */
void PixShot::init()
{
    this->loadModules();
    this->loadInterface();
    this->setConnections();
}

/**
 * Load the modules mainly the preferences
 *
 * @brief AppManager::loadModules
 */
void PixShot::loadModules()
{
    /*
     * All Preferences will be saved in preferences.ini
     */
    try
    {
        if(!QFile::exists(PREFERENCES_FILE))
        {
            Preferences::createDefault(PREFERENCES_FILE);
        }

        preferences = new Preferences(PREFERENCES_FILE);
        preferences->load();

        connect(preferences, SIGNAL(updatePreferences(int)), this, SLOT(updatePreferences(int)));
    }
    catch(...)
    {
        QMessageBox messageBox;
        messageBox.setParent(pixShotInterface);
        messageBox.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        messageBox.resize(500, 100);
        messageBox.setText("Cannot Load Preferences.    ");
        messageBox.setInformativeText("Please <b>Re Install</b> the Application");
        messageBox.setStandardButtons(QMessageBox::Yes);
        messageBox.setDefaultButton(QMessageBox::Yes);
        int result = messageBox.exec();

        switch(result)
        {
            case QMessageBox::Yes :
                    this->quit();
                break;
            case QMessageBox::No:
            default:;
        }
    }
}

/**
 * Set all the top level interface connections
 *
 * @brief AppManager::setConnections
 */
void PixShot::setConnections()
{
    connect(pixShotInterface,SIGNAL(closeApp()),this,SLOT(closeApp()));
    connect(pixShotInterface->actionExit,SIGNAL(triggered()),this,SLOT(closeApp()));
    connect(pixShotInterface->actionCopy,SIGNAL(triggered()),this,SLOT(copyToClipBoard()));
    connect(pixShotInterface->actionPaste,SIGNAL(triggered()),this,SLOT(copyFromClipBoard()));
}

/**
 * Load the interface
 *
 * @brief AppManager::loadInterface
 */
void PixShot::loadInterface()
{
    pixShotInterface = new Interface(this->preferences);

    if(preferences->trayIcon)
    {
        preferences->trayOnStart ? pixShotInterface->hide() : pixShotInterface->showMaximized();
    }
    else
    {
        pixShotInterface->showMaximized();
    }

    this->checkClipboardforImages();
}

/**
 *
 *
 * @brief AppManager::checkClipboardforImages
 */
void PixShot::checkClipboardforImages()
{
    // Check if the clipboard has any images
    try
    {
        const QMimeData *mimeData = QApplication::clipboard()->mimeData();

        if(mimeData->hasImage())
        {
            pixShotInterface->enablePasteOption();
        }
    }
    catch(...)
    {
        // Paste option set to be disabled
    }
}

void PixShot::copyToClipBoard()
{
    QImage image = pixShotInterface->renderSceneToImage();
    QClipboard *clipBoard = QApplication::clipboard();

    try
    {
        clipBoard->setImage(image);
    }
    catch(...)
    {
        pixShotInterface->report(ERROR,"Cannot save image.Clipboard inaccessible.");
        return;
    }
}

void PixShot::copyFromClipBoard()
{
    QClipboard *clipBoard = QApplication::clipboard();
    QImage image;

    try
    {
        image = clipBoard->image();
    }
    catch(...)
    {
        pixShotInterface->report(ERROR,"Cannot copy image. Clipboard inaccessible.");
        return;
    }

    if(!image.isNull())
    {
        this->pixShotInterface->setPixmap(QPixmap::fromImage(image));
    }
    else
    {
        pixShotInterface->report(ERROR,"No Image is available in the Clipboard.");
    }
}

void PixShot::updatePreferences(int preference)
{
    switch(preference)
    {
        case TEXT_ITEM_FONT:
            pixShotInterface->pixShotGraphicsScene->setTextItemFont(preferences->textItemFont);
            break;
        case ITEM_COLOR:
            pixShotInterface->itemProperties->itemColor = preferences->itemColor;
            break;
        case INTERFACE_BG_COLOR:
            pixShotInterface->setBackgroundColor();
            break;
        case TOGGLE_TRAY_ICON:
            pixShotInterface->toggleTrayIcon();
            break;
    }
}

void PixShot::closeApp()
{
    if(!pixShotInterface->isImageAnnotated())
    {
        QMessageBox msgBox;
        msgBox.setParent(pixShotInterface);
        msgBox.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        msgBox.resize(500,100);
        msgBox.setText("You have annotated an image    ");
        msgBox.setInformativeText("Do you wish to <b>Quit</b> without saving them ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch(ret)
        {
            case QMessageBox::Yes :
                    preferences->savePreferences(LOCATIONS);
                    this->quit();
                break;
            case QMessageBox::No :;
        }
    }
    else
    {
        preferences->savePreferences(LOCATIONS);

        qApp->quit();
    }
}

#if defined (Q_OS_WIN)
bool PixShot::winEventFilter(MSG * msg, long * result)
{
    switch(msg->message)
    {
        case WM_HOTKEY:
            this->pixShotInterface->captureRegion();
            break;
    }

    return(false);
}
#endif

PixShot::~PixShot()
{
    delete pixShotInterface;
    delete preferences;
}
