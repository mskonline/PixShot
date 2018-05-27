#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <ui_actionwidget.h>
#include <QButtonGroup>

namespace Ui {
class ActionWidget;
}

class ActionWidget : public QWidget, public Ui::ActionWidget
{
    Q_OBJECT

private:

    QButtonGroup *bGroup;

public:
    explicit ActionWidget(QWidget *parent = 0);
    ~ActionWidget();
    
protected:

    void keyReleaseEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *);

public slots:

    void buttonPressed(int);

signals:

    void action(int);
};

#endif // ACTIONWIDGET_H
