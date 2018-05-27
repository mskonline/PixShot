#include "updatechecker.h"
#include "../../commons/commons.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QUrl>

#include <QDialog>
#include <QLineEdit>
#include <QDomElement>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QMessageBox>

#include <QAuthenticator>
#include <QNetworkProxy>
#include <QNetworkReply>

#define QT_NO_NETWORKPROXY

UpdateChecker::UpdateChecker(QWidget *parent) :
    QWidget(parent,Qt::Window |Qt::WindowCloseButtonHint)
{    
    setupUi(this);
    this->setWindowTitle("Update Check - Current Version : " + VERSION);

    int h_by2 = this->height() / 2;
    int w_by2 = this->width() / 2;
    int p_midX = parent->x() + parent->width() / 2;
    int p_midY = parent->y() + parent->height() / 2;

    this->move(p_midX - w_by2, p_midY - h_by2);
    this->setAttribute(Qt::WA_QuitOnClose);

    this->pb_download->setVisible(false);
    authDialog = NULL;

    connect(pb_download,SIGNAL(released()),this,SLOT(openForDownload()));

    this->checkVersion();
}

void UpdateChecker::checkVersion()
{
    if(!netAccess)
        netAccess = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl(VERSION_URL));
    request.setRawHeader("Cache-Control", "no-cache");
    request.setRawHeader( "User-Agent" , "Mozilla Firefox");
    request.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/xhtml+xml");

    netReply = netAccess->get(request);

    connect(netReply,SIGNAL(readyRead()),this,SLOT(readXML()));
    connect(netReply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));
    connect(netReply,SIGNAL(finished()),this,SLOT(downloadFinished()));
    connect(netAccess,SIGNAL(proxyAuthenticationRequired(const QNetworkProxy, QAuthenticator *)),this,
            SLOT(onAuthRequest(const QNetworkProxy,QAuthenticator *)));
}

void UpdateChecker::readXML()
{
    QByteArray data = netReply->readAll();
    d = new QDomDocument();
    d->setContent(data);

    QDomElement root = d->documentElement();

    QDomNode versions = root.namedItem("versions");
    QDomNode current = versions.namedItem("current");
    this->newVersion = current.namedItem("version").toElement().text();
    this->downloadURL = current.namedItem("url").toElement().text();
    int version = current.namedItem("number").toElement().text().toInt();

    if(version > VERSION_NUMBER) {
        this->l_notify->setText("New version " + this->newVersion + " available.");
        this->pb_download->setVisible(true);
    } else {
        this->l_notify->setText("Your are using the latest version");
    }
}

void UpdateChecker::openForDownload()
{
    QDesktopServices dServices;
    bool status = dServices.openUrl(QUrl(this->downloadURL));

    if(!status)
        QMessageBox::critical(this,"PixShot Error","Some problem has occurred while opening the site. please try again.");

    this->close();
}

void UpdateChecker::downloadFinished()
{
    this->setCheckComplete();
    netReply->deleteLater();
}

void UpdateChecker::error(QNetworkReply::NetworkError error)
{
    this->setCheckComplete();
    this->l_notify->setText("Some problem has occurred while checking for update. please try again.");
}

void UpdateChecker::setCheckComplete()
{
    this->pbar_status->setMaximum(100);
    this->pbar_status->setValue(100);
}

void UpdateChecker::onAuthRequest(const QNetworkProxy nProxy,QAuthenticator *auth)
{
    this->pbar_status->setVisible(false);
    this->l_notify->setVisible(false);

    QLineEdit *le_username;
    QLineEdit *le_password;

    if(!authDialog)
    {
        QPushButton *pb_done, *pb_cancel;
        QLabel *label;
        QLabel *label_2;
        QLabel *lb_hostname;

        authDialog = new QDialog(this, Qt::FramelessWindowHint);

        authDialog->resize(328, 125);
        pb_done = new QPushButton(authDialog);
        pb_done->setObjectName(QString::fromUtf8("pb_done"));
        pb_done->setGeometry(QRect(230, 100, 71, 23));
        pb_done->setDefault(true);
        label = new QLabel(authDialog);
        label->setGeometry(QRect(10, 40, 71, 16));
        label_2 = new QLabel(authDialog);
        label_2->setGeometry(QRect(10, 70, 71, 16));
        le_username = new QLineEdit(authDialog);
        le_username->setGeometry(QRect(70, 40, 231, 20));
        le_password = new QLineEdit(authDialog);
        le_password->setGeometry(QRect(70, 70, 231, 20));
        le_password->setInputMethodHints(Qt::ImhHiddenText);
        le_password->setEchoMode(QLineEdit::Password);
        lb_hostname = new QLabel(authDialog);
        lb_hostname->setGeometry(QRect(10, 10, 291, 21));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lb_hostname->setFont(font);
        pb_cancel = new QPushButton(authDialog);
        pb_cancel->setGeometry(QRect(150, 100, 71, 23));

        pb_done->setText("Done");
        pb_cancel->setText("Cancel");
        label->setText("Username");
        label_2->setText("Password");
        lb_hostname->setText(nProxy.hostName());

        connect(pb_done,SIGNAL(released()),authDialog,SLOT(accept()));
        connect(pb_cancel,SIGNAL(released()),authDialog,SLOT(reject()));
    }

    int hw = this->x() + this->width() / 2;
    int hy = this->y() + 30;

    authDialog->move(hw - authDialog->width() / 2,hy);

    if(authDialog->exec() == QDialog::Accepted)
    {
        this->pbar_status->setVisible(true);
        this->l_notify->setVisible(true);

        auth->setUser(le_username->text().trimmed());
        auth->setPassword(le_password->text());
    }
    else
    {
        delete authDialog;
        this->close();
    }
}

UpdateChecker::~UpdateChecker()
{
    if(authDialog)
        delete authDialog;
}
