#include "textitem.h"
#include <QPainter>
#include <QTextCursor>
#include <QTextDocument>
#include <QStyleOptionGraphicsItem>
#include <QAbstractTextDocumentLayout>
#include <QDebug>


TextItem::TextItem(QGraphicsItem *parent)
{
    this->setParentItem(parent);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void TextItem::focusOutEvent(QFocusEvent * event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    if(textInteractionFlags() == Qt::NoTextInteraction)
       setTextInteractionFlags(Qt::TextEditorInteraction);

    /*QTextCursor cursor = this->textCursor();
    cursor.setPosition(this->toPlainText().length());
    cursor.clearSelection();
    this->setTextCursor(cursor);*/
    /*int pos = this->document()->documentLayout()->hitTest(event->pos(),Qt::FuzzyHit);
    QTextCursor cursor = this->textCursor();
    cursor.setPosition(pos);
    cursor.clearSelection();
    this->setTextCursor(cursor);*/

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    bool _isSelected = option->state & (QStyle::State_Selected | QStyle::State_HasFocus);


    if(_isSelected) {
        QStyleOptionGraphicsItem *style;

        // prevent the dotted selection rectangle
        style = const_cast <QStyleOptionGraphicsItem *> (option);
        style->state &= ~QStyle::State_Selected;
        painter->setPen(Qt::red);
        painter->drawRect(this->boundingRect());
        QGraphicsTextItem::paint(painter,style,widget);
    }
    else
         QGraphicsTextItem::paint(painter,option,widget);
}
