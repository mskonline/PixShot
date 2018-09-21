#include "actionwidget.h"
#include "ui_actionwidget.h"
#include <QKeyEvent>
#include <QDesktopWidget>

#define CLOSED 3

ActionWidget::ActionWidget(QWidget *parent) :
    QWidget(parent,Qt::Window
            | Qt::WindowCloseButtonHint)
{
    setupUi(this);

    QDesktopWidget *dw = QApplication::desktop();
    QSize s = dw->screen(dw->primaryScreen())->size();

    int w_by2 = s.width() / 2;
    int h_by2 = s.height() / 2;

    int p_midX = this->width() / 2;
    int p_midY = this->height() / 2;

    this->move(w_by2 - p_midX, h_by2 - p_midY);

    bGroup = new QButtonGroup();

    bGroup->addButton(pb_edit, 0);
    bGroup->addButton(pb_save,1);
    bGroup->addButton(pb_copy,2);

    connect(bGroup,SIGNAL(buttonReleased(int)),this,SLOT(buttonPressed(int)));
    this->activateWindow();
}

void ActionWidget::buttonPressed(int actionType)
{
    this->hide();
    emit action(actionType);
}

void ActionWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
         case Qt::Key_Escape:
         case Qt::Key_Delete:
            emit action(CLOSED);
            this->close();
            break;
    }
}

void ActionWidget::closeEvent(QCloseEvent *)
{
    this->hide();
    emit action(-1);
}

ActionWidget::~ActionWidget()
{
}
