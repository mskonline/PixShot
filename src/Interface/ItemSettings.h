#ifndef ITEMSETTINGS_H
#define ITEMSETTINGS_H

#include <QWidget>
#include "ui_itemsettings.h"
#include "../Commons/commons.h"

namespace Ui {
    class ItemSettings;
}

class ItemSettings: public QWidget, public Ui::ItemSettings {

    Q_OBJECT

private:
    QColor penColor,
           brushColor,
           fontColor;
    ItemProperties *prop;

public:

    ItemSettings(ItemProperties *prop, QWidget *parent = 0);
    ~ItemSettings();

public slots:

    void setPenColor();
    void setBrushColor();
    void saveSettings();
    void selectFont();
    void setFontColor();
};
#endif // ITEMSETTINGS_H
