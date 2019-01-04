# -------------------------------------------------
# Project created by QtCreator 2012-01-14T23:04:21
# -------------------------------------------------
QT += widgets network xml printsupport
TARGET = PixShot
TEMPLATE = app
SOURCES += main.cpp \
    appmanager/appmanager.cpp \
    interface/interface.cpp \
    graphics/gscene.cpp \
    graphics/items/rectitem.cpp \
    graphics/items/baseitem.cpp \
    interface/toolbox.cpp \
    graphics/items/circleitem.cpp \
    graphics/items/arrowitem.cpp \
    interface/itemsettings.cpp \
    graphics/items/textitem.cpp \
    graphics/items/cropitem.cpp \
    graphics/items/highlighteritem.cpp \
    interface/regioncapturescene.cpp \
    graphics/items/regionselectitem.cpp \
    interface/about.cpp \
    preferences/preferences.cpp \
    interface/PreferenceInterface.cpp \
    interface/filenameprompt.cpp \
    graphics/gpixmap.cpp \
    interface/newpixwidget.cpp \
    interface/widgets/updatechecker.cpp \
    qapp.cpp \
    interface/widgets/actionwidget.cpp \
    graphics/gaction.cpp

HEADERS += appmanager/appmanager.h \
    interface/interface.h \
    graphics/gscene.h \
    graphics/items/rectitem.h \
    graphics/items/baseitem.h \
    interface/toolbox.h \
    graphics/items/circleitem.h \
    commons/commons.h \
    graphics/items/arrowitem.h \
    interface/itemsettings.h \
    graphics/items/textitem.h \
    graphics/items/cropitem.h \
    graphics/items/highlighteritem.h \
    interface/regioncapturescene.h \
    graphics/items/regionselectitem.h \
    interface/about.h \
    preferences/preferences.h \
    interface/PreferenceInterface.h \
    interface/filenameprompt.h \
    graphics/gpixmap.h \
    interface/newpixwidget.h \
    interface/widgets/updatechecker.h \
    qapp.h \
    interface/widgets/actionwidget.h \
    graphics/gaction.h
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
