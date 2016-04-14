# -------------------------------------------------
# Project created by QtCreator 2012-01-14T23:04:21
# -------------------------------------------------
QT += widgets network xml printsupport
TARGET = PixShot
TEMPLATE = app
SOURCES += main.cpp \
    AppManager/appmanager.cpp \
    Interface/interface.cpp \
    Interface/gscene.cpp \
    Interface/items/rectitem.cpp \
    Interface/items/baseitem.cpp \
    Interface/toolbox.cpp \
    Interface/items/circleItem.cpp \
    Interface/items/arrowitem.cpp \
    Interface/itemsettings.cpp \
    Interface/items/textitem.cpp \
    Interface/items/cropitem.cpp \
    Interface/items/highlighteritem.cpp \
    Interface/regioncapturescene.cpp \
    Interface/items/regionselectitem.cpp \
    Interface/about.cpp \
    Preferences/preferences.cpp \
    Interface/PreferenceInterface.cpp \
    Interface/filenameprompt.cpp \
    Interface/gpixmap.cpp \
    Interface/newpixwidget.cpp \
    Interface/widgets/updatechecker.cpp \
    qapp.cpp \
    Interface/widgets/actionwidget.cpp \
    Interface/gaction.cpp

HEADERS += AppManager/appmanager.h \
    Interface/interface.h \
    Interface/gscene.h \
    Interface/items/rectitem.h \
    Interface/items/baseitem.h \
    Interface/toolbox.h \
    Interface/items/circleItem.h \
    Commons/commons.h \
    Interface/items/arrowitem.h \
    Interface/ItemSettings.h \
    Interface/items/textitem.h \
    Interface/items/cropitem.h \
    Interface/items/highlighteritem.h \
    Interface/regioncapturescene.h \
    Interface/items/regionselectitem.h \
    Interface/about.h \
    Preferences/preferences.h \
    Interface/PreferenceInterface.h \
    Interface/filenameprompt.h \
    Interface/gpixmap.h \
    Interface/newpixwidget.h \
    Interface/widgets/updatechecker.h \
    qapp.h \
    Interface/widgets/actionwidget.h \
    Interface/gaction.h
win32:UI_DIR = temp/ui
FORMS += Interface/interface.ui \
    Interface/itemsettings.ui \
    Interface/toolbox.ui \
    Interface/croppanel.ui \
    Interface/about.ui \
    Preferences/preferences.ui \
    Interface/filenameprompt.ui \
    Interface/newpixwidget.ui \
    Interface/widgets/updatechecker.ui \
    Interface/widgets/actionwidget.ui
win32:MOC_DIR = temp/moc
win32:OBJECTS_DIR = temp/obj
win32:RC_FILE = Resources/pixshot.rc
RESOURCES += Resources/resources.qrc
