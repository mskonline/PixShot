#ifndef FILENAMEPROMPT_H
#define FILENAMEPROMPT_H

#include <QWidget>

namespace Ui {
class FileNamePrompt;
}

class FileNamePrompt : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileNamePrompt(QString, QString, QWidget *parent = 0);
    ~FileNamePrompt();
     
private:

    Ui::FileNamePrompt *ui;
    QString location;
    QString format;

protected:

    void keyReleaseEvent(QKeyEvent *);

signals :

    void fileName(QString);

public slots :

    void onSaveClicked();
};

#endif // FILENAMEPROMPT_H
