#ifndef NEWPIXWIDGET_H
#define NEWPIXWIDGET_H

#include "ui_newpixwidget.h"
#include <QButtonGroup>

namespace Ui {
class NewPixWidget;
}

class NewPixWidget : public QWidget, public Ui::NewPixWidget
{
    Q_OBJECT
    
public:

    explicit NewPixWidget(QWidget *parent = 0);
    ~NewPixWidget();

private:

    QButtonGroup *bGroup;

protected:

    void keyReleaseEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);

public slots:

    void buttonPressed(int);

signals:

    void newAction(int);
};

#endif // NEWPIXWIDGET_H
