SOURCES += $$PWD/aboutwidget.cpp \
    $$PWD/aboutwidgetui.cpp

HEADERS += $$PWD/aboutwidget.h \
    $$PWD/aboutwidgetui.h

win32 {
QT += winextras
LIBS += -luser32 -ldwmapi
}

INCLUDEPATH += $$PWD

FORMS += \
    $$PWD/aboutwidgetui.ui

