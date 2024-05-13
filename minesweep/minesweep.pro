#-------------------------------------------------
#
# Project created by QtCreator 2022-04-27T16:40:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minesweep
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    mouseaction.cpp \
    DoAChose.cpp \
    Position.cpp \
    AsForUs.cpp \
    Explain.cpp \
    mainwindow.cpp \
    login.cpp \
    fixpw.cpp

HEADERS += \
    mouseaction.h \
    DoAChose.h \
    Explain.h \
    Position.h \
    AsForUs.h \
    mainwindow.h \
    login.h \
    fixpw.h

FORMS += \
    DoAChose.ui \
    Position.ui \
    AsForUs.ui \
    Explain.ui \
    mainwindow.ui \
    login.ui \
    fixpw.ui

RESOURCES += \
    ohhh.qrc

DISTFILES += \
    p/npc.png \
    p/peace.png \
    p/pia.png

