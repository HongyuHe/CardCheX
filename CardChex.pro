#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T08:38:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardChex
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


SOURCES += \
        main.cpp \
        home_window.cpp \
    welcome_widget.cpp \
    logic_layer.cpp

HEADERS += \
        home_window.h \
    welcome_widget.h \
    logic_layer.h

FORMS += \
        home_window.ui \
    welcome_widget.ui

RESOURCES += \
    pictures.qrc \
    theme/qss.qrc

RC_ICONS = CardCheX.ico

DISTFILES +=
