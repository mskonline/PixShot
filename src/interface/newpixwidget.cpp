#include "newpixwidget.h"
#include "ui_newpixwidget.h"

#include <QKeyEvent>

NewPixWidget::NewPixWidget(QWidget *parent) :
    QWidget(parent,Qt::Window
            | Qt::WindowCloseButtonHint)
{    
    setupUi(this);

    int h_by2 = this->height() / 2;
    int w_by2 = this->width() / 2;
    int p_midX = parent->x() + parent->width() / 2;
    int p_midY = parent->y() + parent->height() / 2;

    this->move(p_midX - w_by2, p_midY - h_by2);

    bGroup = new QButtonGroup();

    bGroup->addButton(pb_open, 0);
    bGroup->addButton(pb_captureRegion,1);
    bGroup->addButton(pb_captureScreen,2);
    bGroup->addButton(pb_clipboard,3);

    connect(bGroup,SIGNAL(buttonReleased(int)),this,SLOT(buttonPressed(int)));
    this->activateWindow();
    this->setFocusProxy(pb_open);
}

void NewPixWidget::buttonPressed(int actionType)
{
    this->hide();
    emit newAction(actionType);
}

void NewPixWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
         case Qt::Key_Escape:
         case Qt::Key_Delete:
            this->hide();
            break;
    }
}

void NewPixWidget::closeEvent(QCloseEvent *)
{
    this->hide();
}

NewPixWidget::~NewPixWidget()
{
}
