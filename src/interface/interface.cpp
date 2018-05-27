#include "about.h"
#include "interface.h"
#include "filenameprompt.h"
#include "widgets/updatechecker.h"

#include <QDebug>
#include <QAction>
#include <QClipboard>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QMessageBox>
#include <QMimeData>
#include <QMatrix>
#include <qmath.h>

#include <windows.h>

Interface::Interface(Preferences *preferences)
{
    this->setupUi(this);
    this->preferences = preferences;

    // Sets Zero Margin
    this->centralWidget()->layout()->setMargin(0);

    zoomStep = 1;
    c_zoom = 1;

    isCtrlPressed = false;

    nPixWidget = NULL;
    sysTrayIcon = NULL;
    actionWidget = NULL;

    init();
    setUpTabBar();
    setUpToolBox();
    setUpActions();

    if(preferences->trayIcon)
        setUpTrayIcon();

    setConnections();

    this->setAcceptDrops(true);
    //this->createNew();
}

void Interface::init()
{
    itemProperties = new ItemProperties;
    itemProperties->itemColor = preferences->itemColor;

    // Set Scene
    gscene = new GScene(itemProperties);
    QBrush brush(preferences->interfaceBGColor);
    brush.setStyle(Qt::SolidPattern);
    this->graphicsView->setBackgroundBrush(brush);

    this->graphicsView->setScene(gscene);

    img = NULL;
    this->dCursor = new QCursor(Qt::ArrowCursor);
    this->toolFrame->setDisabled(true);
    this->tabArea->hide();

    this->actionSave->setDisabled(true);
    this->actionCopy->setDisabled(true);
    this->actionPrint->setDisabled(true);

    // Register Hotkey - TODO
    // RegisterHotKey(this->winId(),100,0,VK_SNAPSHOT);
}

void Interface::setUpTabBar()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this->tabArea);
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0,5,0,0);

    tabBar = new QTabBar(this->tabArea);
    hLayout->addWidget(tabBar);

    tabBar->setMinimumWidth(35);
    tabBar->setTabsClosable(TRUE);
    tabBar->setExpanding(false);
    tabBar->setElideMode(Qt::ElideRight);

    tabChange = new QShortcut(QKeySequence("ctrl+tab"),this);
    tabClose = new QShortcut(QKeySequence("alt+q"),this);
}

void Interface::setConnections()
{
    connect(actionNew,SIGNAL(triggered()),this,SLOT(createNew()));
    connect(actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(actionAbout_Qt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(actionSave,SIGNAL(triggered()),this,SLOT(saveImage()));
    connect(actionPrint,SIGNAL(triggered()),this,SLOT(printImage()));
    connect(actionShow,SIGNAL(triggered()),this,SLOT(showUp()));
    connect(actionRegionCapture,SIGNAL(triggered()),this,SLOT(captureRegion()));
    connect(actionScreenCapture,SIGNAL(triggered()),this,SLOT(captureScreen()));
    connect(actionPreferences,SIGNAL(triggered()),this,SLOT(showPreferences()));
    connect(actionCheck_for_Updates,SIGNAL(triggered()),this,SLOT(checkForUpdates()));
    connect(actionPixShot_Homepage,SIGNAL(triggered()),this,SLOT(openWebsite()));

    connect(tabChange,SIGNAL(activated()),this,SLOT(switchTab()));

    //TODO
    //connect(tabClose,SIGNAL(activated()),this,SLOT(switchTab()));

    connect(toolButton,SIGNAL(buttonReleased(int)),this,SLOT(selectObject(int)));
    connect(pb_Settings,SIGNAL(released()),this,SLOT(openItemSettings()));
    connect(pb_clear,SIGNAL(released()),gscene,SLOT(clearObjects()));

    connect(tabBar,SIGNAL(currentChanged(int)),this,SLOT(setActivePixmap(int)));
    connect(tabBar,SIGNAL(tabCloseRequested(int)),this,SLOT(removePixmap(int)));

    connect(gscene,SIGNAL(resetCursor()),this,SLOT(resetCursor()));
    connect(gscene,SIGNAL(pixmapEdited(bool)),this,SLOT(pixmapEdited(bool)));
    connect(gscene,SIGNAL(releaseCtrl()),this,SLOT(releaseCtrl()));
}

void Interface::setUpToolBox()
{
    toolButton = new QButtonGroup();
    toolButton->addButton(pb_Pointer,0);
    toolButton->addButton(pb_Rectangle,1);
    toolButton->addButton(pb_Circle,2);
    toolButton->addButton(pb_Arrow,3);
    toolButton->addButton(pb_text,4);
    toolButton->addButton(pb_crop,5);
    toolButton->addButton(pb_highligter,6);
    toolButton->setExclusive(true);
}

void Interface::setUpTrayIcon()
{
    sysTrayIcon = new QSystemTrayIcon(QIcon(":/images/images/systray-small.png"),this);

    sysTrayMenu = new QMenu(this);
    sysTrayMenu->addAction(this->actionExit);
    sysTrayMenu->addSeparator();
    sysTrayMenu->addAction(this->actionOpen);
    sysTrayMenu->addAction(this->actionNew);
    sysTrayMenu->addSeparator();
    sysTrayMenu->addAction(this->actionScreenCapture);
    sysTrayMenu->addAction(this->actionRegionCapture);
    sysTrayMenu->addSeparator();
    sysTrayMenu->addAction(this->actionShow);
    sysTrayIcon->setContextMenu(sysTrayMenu);

    sysTrayIcon->setToolTip("PixShot");
    sysTrayIcon->show();

    connect(sysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showTrayMenu(QSystemTrayIcon::ActivationReason)));
    connect(sysTrayIcon,SIGNAL(messageClicked()),this,SLOT(showUp()));
}

void Interface::setBackgroundColor()
{
    QBrush brush(preferences->interfaceBGColor);
    brush.setStyle(Qt::SolidPattern);
    this->graphicsView->setBackgroundBrush(brush);
}

void Interface::setUpActions()
{
    actionShow = new QAction(this);
    actionShow->setText("Pixshot");
    actionShow->setIcon(QIcon(":/images/images/systray-small.png"));
}

void Interface::showTrayMenu(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::MiddleClick:
                this->showUp();
            break;
    }
}

void Interface::showUp()
{
    if(this->isHidden())
        this->show();
    else
        this->showMaximized();
}

void Interface::enablePasteOption(){
    this->actionPaste->setEnabled(true);
}

void Interface::createNew()
{
    if(!nPixWidget)
    {
        nPixWidget = new NewPixWidget(this);

        connect(nPixWidget,SIGNAL(newAction(int)),this,SLOT(setUpNewPix(int)));
    }

    nPixWidget->show();
    this->graphicsView->unsetCursor();
}

void Interface::setUpNewPix(int actionType)
{
    switch(actionType)
    {
        case 0: // open new file
                this->openFile();
                break;
        case 1: // capture region
                this->captureRegion();
                break;
        case 2: // capture screen
                this->captureScreen();
                break;
        case 3: // copy from Clipboard
                this->copyFromClipboard();
                break;
    }
}

void Interface::doAction(int actionType)
{
    QString path;

    switch(actionType)
    {
        case 0: // Edit
            this->setPixmap(capturedPix);
            this->showUp();
            break;
        case 1: // Save
            path = QFileDialog::getSaveFileName(NULL,
                                            tr("Save the image"),
                                            preferences->lastSaveLocation,
                                            tr("Image Files (*.png *.jpeg *.jpg)"));

            if(path.isEmpty())
                return;

            path = checkFileName(path);
            capturedPix.save(path);
            break;
        case 2: // Copy to Clipboard
            this->copyToClipboard();
            break;
        default:;
        // Do nothing
    }
}

void Interface::openItemSettings()
{
    itemSettings = new ItemSettings(itemProperties,this);
    itemSettings->show();
}

void Interface::showPreferences()
{
     preferences->showPreferences(this);
}

void Interface::openFile()
{
    QString filePath;

    filePath = QFileDialog::getOpenFileName(this,
                                            tr("Open an Image"),
                                            preferences->lastOpenLocation,
                                            tr("Image Files (*.png *.jpeg *.jpg)"));

    if(!filePath.isEmpty())
    {
        gscene->setPixmap(QPixmap(filePath));
        this->addTab();
        tabBar->setCurrentIndex(tabBar->count() - 1);
        this->graphicsView->unsetCursor();
        preferences->lastOpenLocation = filePath.section("/",0,-2);
    }
}

void Interface::copyFromClipboard()
{
    QClipboard *clipBoard = QApplication::clipboard();
    QImage img;

    try
    {
        img = clipBoard->image();
    }
    catch(...)
    {
        this->report(ERROR,"Cannot copy image. Clipboard inaccessible.");
        return;
    }

    if(!img.isNull())
    {
        this->setPixmap(QPixmap::fromImage(img));
    }
    else
    {
        this->report(INFO,"No images available in Clipboard");
    }
}

void Interface::copyToClipboard()
{
    QImage img = capturedPix.toImage();
    QClipboard *clipBoard = QApplication::clipboard();

    try
    {
        clipBoard->setImage(img);
    }
    catch(...)
    {
        this->report(ERROR,"Cannot save image.Clipboard inaccessible.");
        return;
    }
}

void Interface::setPixmap(QPixmap p)
{
    gscene->setPixmap(p);

    this->addTab();
    tabBar->setCurrentIndex(tabBar->count() - 1);
    this->graphicsView->unsetCursor();
}

void Interface::removePixmap(int i)
{
    bool close = true;

    if(gscene->isModifed(i)){
        QMessageBox msgBox;
        msgBox.setParent(this);
        msgBox.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        msgBox.resize(500,100);
        msgBox.setText("You have annotated an image    ");
        msgBox.setInformativeText("Do you wish to <b>Close</b> without saving them ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch(ret)
        {
            case QMessageBox::Yes:
                    close = true;
                break;
            case QMessageBox::No:
                    close = false;
        }
    }

    if(close)
    {
        tabBar->removeTab(i);
        gscene->removePixmap(i);

        if(tabBar->count() == 0)
        {
          this->tabArea->hide();
          //this->toolFrame->setDisabled(true);

          // Disable Actions
          this->actionSave->setDisabled(true);
          this->actionCopy->setDisabled(true);
          this->actionPrint->setDisabled(true);

          // Reset Cursor
          this->graphicsView->setCursor(QCursor(Qt::ArrowCursor));

          this->setCursor(QCursor(Qt::ArrowCursor));
          //this->graphicsView->viewport()->unsetCursor();
          //this->createNew();
        }
    }
}

void Interface::pixmapEdited(bool s)
{
    int currentTab;
    QString label;

    if(s)
    {
        currentTab = tabBar->currentIndex();
        label = tabBar->tabText(currentTab) + "*";
        tabBar->setTabText(currentTab,label);
    }
    else
    {
        currentTab = tabBar->currentIndex();
        label = tabBar->tabText(currentTab).remove(QChar('*'));
        tabBar->setTabText(currentTab,label);
    }
}

void Interface::saveImage()
{
    QString path,format;

    if(preferences->toPreferedLocation)
    {
        path = preferences->saveLocation;
        format = preferences->imageFormat;
        FileNamePrompt *fnp = new FileNamePrompt(path,format,this);

        connect(fnp,SIGNAL(fileName(QString)),this,SLOT(saveToFile(QString)));

        fnp->show();
        return;
    }
    else
        path = QFileDialog::getSaveFileName(NULL,
                                            tr("Save the image"),
                                            preferences->lastSaveLocation,
                                            tr("Image Files (*.png *.jpeg *.jpg)"));

    try
    {
        if(path.isEmpty())
            return;

        this->saveToFile(path);
    }
    catch(...) /* Generic Catch */
    {
        this->report(ERROR,"Cannot save image.");
    }

    preferences->lastSaveLocation = path.section("/",0,-2);

    // Set Tab Name
    int currTab = tabBar->currentIndex();
    tabBar->setTabText(currTab,path.section('/',-1));
}

QString Interface::checkFileName(QString fname)
{
    QString name = fname;

    if(!name.endsWith(preferences->imageFormat))
        name += preferences->imageFormat;

    return name;
}

QString Interface::toFilePath(QUrl url)
{
    return url.toString().remove(0,8);
}

void Interface::printImage()
{
    if(this->tabBar->count() != 0)
    {
        this->gscene->renderToPrinter();
    }
}

void Interface::selectObject(int id)
{
    this->graphicsView->viewport()->unsetCursor();

    gscene->OBJECT_TYPE = OBJECTS(id);
    bool draw = true;
    bool toolsVisible = true;

    // Change Mouse Cursor
    QString cImg;
    switch(gscene->OBJECT_TYPE)
    {
        case POINTER:
            cImg = ":/images/images/pointer.png";
            draw = false;
            break;
        case RECTANGLE:
        case CIRCLE:
        case ARROW:
        case TEXT:
        case CROP:
            cImg = ":/images/images/crosswire.png";
            break;
        case HIGHLIGHT:
            cImg = ":/images/images/highlighter.png";
    }

    gscene->DRAW_MODE = draw;
    gscene->setSelectionMode(!draw);
    QPixmap p(cImg);
    QCursor c(p);

    this->graphicsView->viewport()->setCursor(c);
    this->toolFrame->setVisible(toolsVisible);
}

void Interface::saveToFile(QString path)
{
    gscene->renderToFile(path);

    int currTab = tabBar->currentIndex();
    tabBar->setTabText(currTab,path.section('/',-1));
}

QImage Interface::renderSceneToImage()
{
    QImage img(gscene->sceneRect().size().toSize(),QImage::Format_RGB32);
    QPainter *painter = new QPainter(&img);

    gscene->render(painter);
    painter->end();
    painter->save();
    delete painter;

    return img;
}

void Interface::zoomIn()
{
    ++zoomStep;
    c_zoom = qPow(qreal(2),(zoomStep - 1)/qreal(50));

    QMatrix matrix;
    matrix.scale(c_zoom,c_zoom);

    this->graphicsView->setMatrix(matrix);
}

void Interface::zoomOut()
{
    --zoomStep;
    c_zoom = qPow(qreal(2),(zoomStep - 1)/qreal(50));

    QMatrix matrix;
    matrix.scale(c_zoom,c_zoom);

    this->graphicsView->setMatrix(matrix);
}

void Interface::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu menu;
    menu.addAction(this->actionNew);
    menu.addSeparator();
    menu.addAction(this->actionPaste);
    menu.addAction(this->actionCopy);
    menu.addAction(this->actionPaste);
    menu.addSeparator();
    menu.addAction(this->actionOpen);
    menu.addAction(this->actionSave);
    menu.addSeparator();
    menu.addAction(this->actionExit);

    if(this->tabBar->count() == 0)
    {
        this->actionSave->setDisabled(true);
        this->actionCopy->setDisabled(true);
        this->actionPrint->setDisabled(true);
    }

    menu.exec(e->globalPos());
}

void Interface::keyPressEvent(QKeyEvent *e)
{
    int k = e->key();

    switch (k) {
    case Qt::Key_Control:
            isCtrlPressed = true;
        break;
    case Qt::Key_Up:
            this->zoomOut();
        break;
    case Qt::Key_Down:
            this->zoomIn();
        break;
    default:
        e->ignore();
        break;
    }
}

void Interface::keyReleaseEvent(QKeyEvent *e)
{
    int k = e->key();

    switch (k) {
    case Qt::Key_Control:
            isCtrlPressed = false;
        break;
    default:
        e->ignore();
        break;
    }
}

void Interface::wheelEvent(QWheelEvent *e)
{
    if(isCtrlPressed)
    {
        if(e->delta() > 0)
            this->zoomOut();
        else
            this->zoomIn();
    }
    else
        e->ignore();
}

void Interface::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void Interface::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void Interface::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void Interface::dropEvent(QDropEvent *event)
{
    const QMimeData *md = event->mimeData();
    if(md->hasImage())
    {
        QImage img = qvariant_cast<QImage>(md->imageData());
        this->setPixmap(QPixmap::fromImage(img));
    }
    else if(md->hasUrls())
    {
        QList<QUrl> lt = md->urls();

        try {
            if(!lt.isEmpty()) {
                QPixmap p(toFilePath(lt.at(ZERO)));
                this->setPixmap(p);
            }
        } catch (...)
        {
            this->report(ERROR,"Cannot open.");
            return;
        }
    }

    event->acceptProposedAction();
}

void Interface::releaseCtrl()
{
    isCtrlPressed = false;
}

void Interface::resetCursor()
{

    //this->toolButton->setExclusive(false);

    //this->pb_crop->setChecked(false);
    this->pb_Pointer->setChecked(true);
    this->selectObject(POINTER);

    //this->toolButton->setExclusive(true);
}

void Interface::captureRegion()
{
    if(!this->isHidden())
        this->hide();

    // refresh the interface
    this->update();
    Delay::sleep(2);

    QPixmap desktopPix;
    desktopPix = QPixmap::grabWindow(QApplication::desktop()->winId());

    QDesktopWidget *desktopWidget = qApp->desktop();
    QRect screenGeo = desktopWidget->screenGeometry();


    regionShotView = new QGraphicsView();
    regionShotView->setSceneRect(QRectF(screenGeo));
    regionShotView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    regionShotView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    regionCaptureScene = new RegionCaptureScene(desktopPix);
    regionShotView->setScene(regionCaptureScene);
    regionShotView->showFullScreen();

    QPixmap p(":/images/images/crosswire.png");
    QCursor c(p);
    regionShotView->viewport()->setCursor(c);

    connect(regionCaptureScene,SIGNAL(closeView()),this,SLOT(closeRegionCapture()));
}

void Interface::closeRegionCapture()
{
    if(!regionCaptureScene->regionPix.isNull())
    {
        capturedPix = regionCaptureScene->regionPix;

        if(!actionWidget)
        {
            actionWidget = new ActionWidget(this);
            connect(actionWidget,SIGNAL(action(int)),this,SLOT(doAction(int)));
        }

        actionWidget->show();
    }

    regionShotView->setVisible(false);
    delete regionCaptureScene;
    delete regionShotView;

    this->graphicsView->setCursor(QCursor(Qt::ArrowCursor));
}

void Interface::captureScreen()
{
    if(!this->isHidden())
        this->hide();

    Delay::sleep(2);

    QDesktopWidget *dw = QApplication::desktop();
    capturedPix = QPixmap::grabWindow(dw->screen(dw->primaryScreen())->winId());

    if(!actionWidget)
    {
        actionWidget = new ActionWidget(this);
        connect(actionWidget,SIGNAL(action(int)),this,SLOT(doAction(int)));
    }

    actionWidget->show();
}

bool Interface::isImageAnnotated()
{
    this->gscene->checkForAllSaved();
}

void Interface::setActivePixmap(int i)
{
    QMatrix matrix;

    // return when last tab is closed
    if(i == -1) {
        this->c_zoom = 1;
    } else {
        // Save Zoom State
        gscene->setPixScale(c_zoom);
        gscene->setZoomStep(zoomStep);

        gscene->setActivePixmap(i);

        this->zoomStep = gscene->getZoomStep();
        this->c_zoom = gscene->getPixScale();
    }

    matrix.scale(c_zoom,c_zoom);
    this->graphicsView->setMatrix(matrix);
}

void Interface::addTab()
{
    if(this->tabBar->count() == 0)
    {
        this->tabArea->show();
        this->toolFrame->setDisabled(false);

        // Enable Actions
        this->actionSave->setDisabled(false);
        this->actionCopy->setDisabled(false);
        this->actionPrint->setDisabled(false);
    }

    QString boardNum;
    boardNum.setNum(this->tabBar->count() + 1);

    tabBar->addTab("Board " + boardNum);
}

void Interface::switchTab()
{
    int numTabs = tabBar->count();

    if(numTabs == 0 || numTabs == 1)
        return;

    int currTab = tabBar->currentIndex();

    int nextTab = (currTab + 1) % numTabs;
    tabBar->setCurrentIndex(nextTab);
}

void Interface::toggleTrayIcon()
{
    if(preferences->trayIcon)
    {
        if(this->sysTrayIcon)
            sysTrayIcon->show();
        else
            this->setUpTrayIcon();
    }
    else
    {
        if(this->sysTrayIcon)
            sysTrayIcon->hide();
    }
}

void Interface::checkForUpdates()
{
    UpdateChecker *updCheck =  new UpdateChecker(this);
    updCheck->show();
}

void Interface::openWebsite()
{
    QDesktopServices dServices;
    bool status = dServices.openUrl(QUrl(WEBSITE));

    if(!status)
        this->report(ERROR,"Some problem has occurred while opening the site. please try again.");
}

void Interface::showAbout()
{
    About *abt = new About(this);
    abt->show();
}

void Interface::aboutQt()
{
    QApplication::aboutQt();
}

void Interface::report(int type, QString msg)
{
    switch(type)
    {
    case ERROR : // Error
        QMessageBox::critical (this,"PixShot Error",msg);
        break;
    case WARNING: // Warning
        QMessageBox::warning(this,"PixShot Warning",msg);
        break;
    case INFO: // Information
        QMessageBox::information(this,"PixShot Information",msg);
    }
}

void Interface::closeEvent(QCloseEvent *e)
{
    if(preferences->toTrayOnClose)
    {
        this->hide();
        e->ignore();
    }
    else
        emit closeApp();
}

Interface::~Interface()
{
    if(sysTrayIcon){
        sysTrayIcon->hide();
        delete sysTrayIcon;
    }

    delete this->gscene;
}
