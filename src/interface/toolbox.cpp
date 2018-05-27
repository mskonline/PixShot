#include "toolbox.h"


ToolBox::ToolBox(QWidget *parent):QWidget(parent,Qt::Tool)
{
    setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);
}

ToolBox::~ToolBox()
{

}
