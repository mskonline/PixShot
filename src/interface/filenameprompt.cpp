#include "filenameprompt.h"
#include "ui_filenameprompt.h"
#include <QKeyEvent>

FileNamePrompt::FileNamePrompt(QString location, QString format, QWidget *parent) :
    QWidget(parent,Qt::Window | Qt::WindowCloseButtonHint),
    ui(new Ui::FileNamePrompt)
{
    ui->setupUi(this);
    this->location = location;
    this->format = format;

    ui->lb_location->setText(tr("File will be saved to <br>") + location);

    connect(ui->pb_save,SIGNAL(released()),this,SLOT(onSaveClicked()));
    connect(ui->le_filename,SIGNAL(returnPressed()),this,SLOT(onSaveClicked()));
    connect(ui->pb_cancel,SIGNAL(released()),this,SLOT(close()));

    int h_by2 = this->height() / 2;
    int w_by2 = this->width() / 2;
    int p_midX = parent->x() + parent->width() / 4;
    int p_midY = parent->y() + parent->height() / 4;

    this->move(p_midX - w_by2, p_midY - h_by2) ;

    setAttribute(Qt::WA_DeleteOnClose);
}

void FileNamePrompt::onSaveClicked()
{
    if(!ui->le_filename->text().isEmpty())
    {
        QString filename;
        QString name = ui->le_filename->text();

        if(!name.endsWith(format))
            name += format;

        filename = this->location + name;
        emit fileName(filename);

        this->close();
    }
}

void FileNamePrompt::keyReleaseEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
         case Qt::Key_Escape:
         case Qt::Key_Delete:
            this->close();
            break;
    }
}

FileNamePrompt::~FileNamePrompt()
{
    delete ui;
}
