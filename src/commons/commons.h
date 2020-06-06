#ifndef COMMONS_H
#define COMMONS_H

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QThread>

#define ZERO 0

enum MSG_TYPES {
    ERROR,
    WARNING,
    INFO
};

/* Initial Settings */
const int initialPenWidth = 3;


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
