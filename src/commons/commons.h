#ifndef COMMONS_H
#define COMMONS_H

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QThread>

#define ZERO 0
#define NORMAL_RUN 0
#define APP_NAME "PixShot"
#define APP_VERSION "0.1"
#define APP_WEBSITE "http://www.pixshot.org"

enum OBJECTS {
    POINTER, /* Item Selection */
    RECTANGLE,
    CIRCLE,
    ARROW,
    TEXT,
    CROP,
    HIGHLIGHT /* Highlighter */
};

enum action {
    CREATE,MOVE,DELETE,DELETE_ALL,IMG_CROP
};

enum MSG_TYPES {
    ERROR,
    WARNING,
    INFO
};

enum PREFERENCES {
    LOCATIONS,
    SAVE_LOCATION,
    IMAGE_FORMAT,
    TEXT_ITEM_FONT,
    ITEM_COLOR,
    INTERFACE_BG_COLOR,
    TO_TRAY_ONCLOSE,
    TOGGLE_TRAY_ICON,
    TO_TRAY_ON_START,
    UPDATE_ON_START
};

/* Initial Settings */
const int initialPenWidth = 3;
const int VERSION_NUMBER = 900;
const QString VERSION = "0.9";
const QString PREFERENCES_FILE = "./preferences.ini";
const QString WEBSITE = "http://www.pixshot.org";
const QString VERSION_URL = "http://www.pixshot.org/info/pixshot.xml";
const QString APP_STYLE = "QTabBar::tab {min-width: 150px; max-width: 150px;}";
const QString LIB_PATH = "./plugins";

class ItemProperties
{
public :

    QColor itemColor,
           fontColor;
    QPen itemPen;
    QBrush itemBrush;
    QFont font;


    ItemProperties()
    {
        itemColor = QColor(Qt::red);
        fontColor = QColor(Qt::red);
        itemPen = QPen(itemColor);
        itemPen.setWidth(initialPenWidth);
        itemBrush = QBrush(itemColor,Qt::NoBrush);
    }

    void setProperties(QColor color, QPen pen, QBrush brush, QColor fontColor)
    {
        itemColor = color;
        fontColor = fontColor;
        itemPen = pen;
        itemBrush = brush;
    }
};

class Delay : public QThread
{
public :
    static void sleep(int secs)
    {
        QThread::sleep(secs);
    }
};

#endif // COMMONS_H
