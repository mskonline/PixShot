#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include "ui_about.h"

namespace Ui {
    class About;
}

class About : public QWidget, public Ui::About
{
    Q_OBJECT
    
public:
    About(QWidget *parent = 0);

};

#endif // ABOUT_H
