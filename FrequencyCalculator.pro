#-------------------------------------------------
#
# Project created by QtCreator 2019-01-23T15:45:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FrequencyCalculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#--------------------------------------------------------------------------------------------
#编译目录配置
MOC_DIR     = $$OUT_PWD/moc
OBJECTS_DIR = $$OUT_PWD/obj
RCC_DIR     = $$OUT_PWD/resource
UI_DIR      = $$OUT_PWD/ui
DESTDIR     = bin


RC_ICONS = logo/logo.ico

include(Frameless/frameless.pri)
include(AboutUI/AboutUI.pri)
include(MainUI/MainUI.pri)

SOURCES += \
        main.cpp

HEADERS += \
    appversions.h

RESOURCES += \
    source.qrc
