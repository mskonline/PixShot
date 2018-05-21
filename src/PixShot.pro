# -------------------------------------------------
# Project created by QtCreator 2012-01-14T23:04:21
# -------------------------------------------------
QT += widgets network xml printsupport
TARGET = PixShot
TEMPLATE = app
SOURCES += main.cpp \
    appmanager/appmanager.cpp \
    interface/interface.cpp \
    interface/gscene.cpp \
    interface/items/rectitem.cpp \
    interface/items/baseitem.cpp \
    interface/toolbox.cpp \
    interface/items/circleItem.cpp \
    interface/items/arrowitem.cpp \
    interface/itemsettings.cpp \
    interface/items/textitem.cpp \
    interface/items/cropitem.cpp \
    interface/items/highlighteritem.cpp \
    interface/regioncapturescene.cpp \
    interface/items/regionselectitem.cpp \
    interface/about.cpp \
    preferences/preferences.cpp \
    interface/PreferenceInterface.cpp \
    interface/filenameprompt.cpp \
    interface/gpixmap.cpp \
    interface/newpixwidget.cpp \
    interface/widgets/updatechecker.cpp \
    qapp.cpp \
    interface/widgets/actionwidget.cpp \
    interface/gaction.cpp

HEADERS += appmanager/appmanager.h \
    interface/interface.h \
    interface/gscene.h \
    interface/items/rectitem.h \
    interface/items/baseitem.h \
    interface/toolbox.h \
    interface/items/circleItem.h \
    commons/commons.h \
    interface/items/arrowitem.h \
    interface/ItemSettings.h \
    interface/items/textitem.h \
    interface/items/cropitem.h \
    interface/items/highlighteritem.h \
    interface/regioncapturescene.h \
    interface/items/regionselectitem.h \
    interface/about.h \
    preferences/preferences.h \
    interface/PreferenceInterface.h \
    interface/filenameprompt.h \
    interface/gpixmap.h \
    interface/newpixwidget.h \
    interface/widgets/updatechecker.h \
    qapp.h \
    interface/widgets/actionwidget.h \
    interface/gaction.h
win32:UI_DIR = temp/ui
FORMS += interface/interface.ui \
    interface/itemsettings.ui \
    interface/toolbox.ui \
    interface/croppanel.ui \
    interface/about.ui \
    preferences/preferences.ui \
    interface/filenameprompt.ui \
    interface/newpixwidget.ui \
    interface/widgets/updatechecker.ui \
    interface/widgets/actionwidget.ui
win32:MOC_DIR = temp/moc
win32:OBJECTS_DIR = temp/obj
win32:RC_FILE = Resources/pixshot.rc
RESOURCES += Resources/resources.qrc
