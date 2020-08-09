# -------------------------------------------------
# Project created by QtCreator 2012-01-14T23:04:21
# -------------------------------------------------
QT += widgets network xml printsupport
TARGET = PixShot
TEMPLATE = app
SOURCES += main.cpp \
    graphics/items/abstractitem.cpp \
    graphics/items/arrow.cpp \
    graphics/items/circle.cpp \
    graphics/items/crop.cpp \
    graphics/items/highlighter.cpp \
    graphics/items/rectangle.cpp \
    graphics/items/regionselect.cpp \
    graphics/items/resizers.cpp \
    graphics/items/text.cpp \
    graphics/pixshotgraphicsscene.cpp \
    interface/interface.cpp \
    interface/preferenceinterface.cpp \
    interface/toolbox.cpp \
    interface/itemsettings.cpp \
    interface/regioncapturescene.cpp \
    interface/about.cpp \
    pixshot.cpp \
    preferences/preferences.cpp \
    interface/filenameprompt.cpp \
    graphics/gpixmap.cpp \
    interface/newpixwidget.cpp \
    interface/widgets/updatechecker.cpp \
    interface/widgets/actionwidget.cpp \
    graphics/gaction.cpp

HEADERS += interface/interface.h \
    constants/application.h \
    constants/preference.h \
    graphics/constants/graphics.h \
    graphics/items/abstractitem.h \
    graphics/items/arrow.h \
    graphics/items/circle.h \
    graphics/items/crop.h \
    graphics/items/highlighter.h \
    graphics/items/rectangle.h \
    graphics/items/regionselect.h \
    graphics/items/resizers.h \
    graphics/items/text.h \
    graphics/pixshotgraphicsscene.h \
    interface/preferenceinterface.h \
    interface/toolbox.h \
    commons/commons.h \
    interface/itemsettings.h \
    interface/regioncapturescene.h \
    interface/about.h \
    pixshot.h \
    preferences/preferences.h \
    interface/filenameprompt.h \
    graphics/gpixmap.h \
    interface/newpixwidget.h \
    interface/widgets/updatechecker.h \
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
