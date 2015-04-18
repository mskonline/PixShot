#include "about.h"
#include "ui_about.h"
#include "../Commons/commons.h"

About::About(QWidget *parent) :
    QWidget(parent,Qt::Window | Qt::WindowCloseButtonHint)
{
    setupUi(this);

    int h_by2 = this->height() / 2;
    int w_by2 = this->width() / 2;
    int p_midX = parent->x() + parent->width() / 2;
    int p_midY = parent->y() + parent->height() / 2;

    this->move(p_midX - w_by2, p_midY - h_by2) ;
    this->setAttribute(Qt::WA_QuitOnClose);
}
