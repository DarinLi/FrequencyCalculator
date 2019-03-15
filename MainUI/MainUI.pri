SOURCES += $$PWD/mainwidget.cpp \
    $$PWD/mainwidgetui.cpp \
    $$PWD/flowlayout.cpp \
    $$PWD/customsql.cpp

HEADERS += $$PWD/mainwidget.h \
    $$PWD/mainwidgetui.h \
    $$PWD/flowlayout.h \
    $$PWD/customsql.h

win32 {
QT += winextras
LIBS += -luser32 -ldwmapi
}

INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/mainwidgetui.ui

