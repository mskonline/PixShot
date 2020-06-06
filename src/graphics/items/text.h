#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include "../../commons/commons.h"

class Text : public QGraphicsTextItem
{
    Q_OBJECT

public:

    Text(QGraphicsItem *parent = 0);
    void focusOutEvent(QFocusEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void lostFocus(Text *);
};

#endif // TEXTITEM_H

/*
 *QPalette p;
p.setBrush(QPalette::Active, QPalette::Highlight, QBrush(QColor("pink")));
p.setBrush(QPalette::Inactive, QPalette::Highlight, QBrush(QColor("pink")));
p.setBrush(QPalette::Active, QPalette::HighlightedText, QBrush(QColor("green")));
p.setBrush(QPalette::Inactive, QPalette::HighlightedText, QBrush(QColor("green")));
QApplication::setPalette(p, "QTextControl");
 */
