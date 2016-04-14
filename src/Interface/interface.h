#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QButtonGroup>
#include <QMenu>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QShortcut>
#include <QSystemTrayIcon>
#include "ui_interface.h"
#include "gscene.h"
#include "regioncapturescene.h"
#include "ItemSettings.h"
#include "../Preferences/preferences.h"
#include "../Commons/commons.h"
#include "newpixwidget.h"
#include "widgets/actionwidget.h"

namespace Ui {
    class Interface;
}

class Interface : public QMainWindow, public Ui::Interface
{
    Q_OBJECT

public:

    GScene *gscene;
    ItemSettings *itemSettings;
    ItemProperties *itemProperties;
    QButtonGroup *toolButton;
    QShortcut *save;
    QTabBar *tabBar;

    Interface(Preferences *);
    ~Interface();

    bool isImageAnnotated();
    void setPixmap(QPixmap);
    void report(int, QString);
    void setBackgroundColor();
    QImage renderSceneToImage();

private:

    QGraphicsPixmapItem *img;
    QGraphicsView *regionShotView;
    RegionCaptureScene *regionCaptureScene;
    QPixmap capturedPix;
    QCursor *dCursor;
    QShortcut *undo;
    QSystemTrayIcon *sysTrayIcon;
    QMenu *sysTrayMenu;
    QShortcut *tabChange, *tabClose;
    QAction *actionShow;
    Preferences *preferences;
    NewPixWidget *nPixWidget;
    ActionWidget *actionWidget;

    int zoomStep;
    qreal c_zoom;
    bool isCtrlPressed;

    void init();
    void setUpTabBar();
    void setUpToolBox();
    void setUpTrayIcon();
    void setConnections();
    void setUpActions();
    void addTab();
    void copyFromClipboard();
    void copyToClipboard();
    QString checkFileName(QString);
    QString toFilePath(QUrl);

    void closeEvent(QCloseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *);

    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dropEvent(QDropEvent *);

signals:

    void closeApp();

public slots:

    void openFile();
    void createNew();
    void showAbout();
    void aboutQt();
    void saveImage();
    void printImage();
    void selectObject(int);
    void openItemSettings();
    void resetCursor();
    void captureRegion();
    void captureScreen();
    void closeRegionCapture();
    void removePixmap(int);
    void saveToFile(QString);
    void showTrayMenu(QSystemTrayIcon::ActivationReason);
    void showPreferences();
    void setUpNewPix(int);
    void pixmapEdited(bool);
    void setActivePixmap(int);
    void enablePasteOption();
    void checkForUpdates();
    void openWebsite();
    void switchTab();
    void releaseCtrl();
    void showUp();
    void doAction(int);
    void toggleTrayIcon();

    void zoomIn();
    void zoomOut();
};

#endif // INTERFACE_H
