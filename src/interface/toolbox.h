#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include "ui_toolbox.h"

namespace Ui {
    class ToolBox;
}

class ToolBox: public QWidget, public Ui::ToolBox
{
    Q_OBJECT

public:

    ToolBox(QWidget *parent = 0);
    ~ToolBox();
};

#endif // TOOLBOX_H
