SOURCES += $$PWD/framelesshelper.cpp \
    $$PWD/customwidget.cpp

HEADERS += $$PWD/framelesshelper.h \
    $$PWD/customwidget.h

win32 {
QT += winextras
LIBS += -luser32 -ldwmapi
}

INCLUDEPATH += $$PWD

