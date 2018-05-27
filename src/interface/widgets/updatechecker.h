#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QDomDocument>
#include "ui_updatechecker.h"

namespace Ui {
class UpdateChecker;
}

class UpdateChecker : public QWidget, public Ui::UpdateChecker
{
    Q_OBJECT
private:
    QNetworkAccessManager *netAccess;
    QNetworkReply *netReply;
    QDomDocument *d;
    QDialog *authDialog;

    QString newVersion;
    QString downloadURL;
    void setCheckComplete();

public:
    explicit UpdateChecker(QWidget *parent = 0);
    ~UpdateChecker();

public slots:

    void checkVersion();
    void readXML();
    void openForDownload();
    void downloadFinished();
    void error(QNetworkReply::NetworkError);
    void onAuthRequest(const QNetworkProxy proxy ,QAuthenticator *auth);
};

#endif // UPDATECHECKER_H
