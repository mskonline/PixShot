#include "appmanager.h"
#include <QDebug>
#include <QFile>
#include <QMimeData>
#include <QMessageBox>

/**
 * Constructor
 *
 * @brief AppManager::AppManager
 */
AppManager::AppManager()
{
}

/**
 * Init method to intialize the modules, interface and the connections
 *
 * @brief AppManager::init
 */
void AppManager::init()
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
void AppManager::loadModules()
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

        connect(preferences,SIGNAL(updatePreferences(int)),this,SLOT(updatePreferences(int)));
    }
    catch(...)
    {
        QMessageBox msgBox;
        msgBox.setParent(interface);
        msgBox.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        msgBox.resize(500,100);
        msgBox.setText("Cannot Load Preferences.    ");
        msgBox.setInformativeText("Please <b>Re Install</b> the Application");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch(ret)
        {
            case QMessageBox::Yes :
                    qApp->quit();
                break;
        }
    }
}

/**
 * Set all the top level interface connections
 *
 * @brief AppManager::setConnections
 */
void AppManager::setConnections()
{
    connect(interface,SIGNAL(closeApp()),this,SLOT(closeApp()));
    connect(interface->actionExit,SIGNAL(triggered()),this,SLOT(closeApp())); 
    connect(interface->actionCopy,SIGNAL(triggered()),this,SLOT(copyToClipBoard()));
    connect(interface->actionPaste,SIGNAL(triggered()),this,SLOT(copyFromClipBoard()));
}

/**
 * Load the interface
 *
 * @brief AppManager::loadInterface
 */
void AppManager::loadInterface()
{
    interface = new Interface(this->preferences);

    if(preferences->trayIcon)
    {
        preferences->trayOnStart ? interface->hide() : interface->showMaximized();
    }
    else
    {
        interface->showMaximized();
    }

    this->checkClipboardforImages();
}

/**
 *
 *
 * @brief AppManager::checkClipboardforImages
 */
void AppManager::checkClipboardforImages()
{
    // Check if the clipboard has any images
    try
    {
        const QMimeData *mimeData = QApplication::clipboard()->mimeData();

        if(mimeData->hasImage()){
            interface->enablePasteOption();
        }
    }
    catch(...)
    {
        // Paste option set to be disabled
    }
}

void AppManager::activateRegionCapture()
{
    this->interface->captureRegion();
}

void AppManager::copyToClipBoard()
{
    QImage img = interface->renderSceneToImage();
    QClipboard *clipBoard = QApplication::clipboard();

    try
    {
        clipBoard->setImage(img);
    }
    catch(...)
    {
        interface->report(ERROR,"Cannot save image.Clipboard inaccessible.");
        return;
    }
}

void AppManager::copyFromClipBoard()
{
    QClipboard *clipBoard = QApplication::clipboard();
    QImage img;

    try
    {
        img = clipBoard->image();
    }
    catch(...)
    {
        interface->report(ERROR,"Cannot copy image. Clipboard inaccessible.");
        return;
    }

    if(!img.isNull())
    {
        this->interface->setPixmap(QPixmap::fromImage(img));
    }
    else
    {
        interface->report(ERROR,"No Image is available in the Clipboard.");
    }
}

void AppManager::updatePreferences(int pref)
{
    switch(pref)
    {
        case TEXT_ITEM_FONT:
            interface->gscene->setTextItemFont(preferences->textItemFont);
            break;
        case ITEM_COLOR:
            interface->itemProperties->itemColor = preferences->itemColor;
            break;
        case INTERFACE_BG_COLOR:
            interface->setBackgroundColor();
            break;
        case TOGGLE_TRAY_ICON:
            interface->toggleTrayIcon();
            break;
    }
}

void AppManager::closeApp()
{
    if(!interface->isImageAnnotated())
    {
        QMessageBox msgBox;
        msgBox.setParent(interface);
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
                    qApp->quit();
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

AppManager::~AppManager()
{
    delete interface;
    delete preferences;
}

