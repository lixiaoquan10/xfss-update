#-------------------------------------------------
#
# Project created by QtCreator 2024-02-26T22:22:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = update
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        softwareUpdate.cpp\
        mountUSB.cpp\
        mainPicture.cpp

HEADERS  += mainwindow.h\
        softwareUpdate.h\
        mountUSB.h\
        mainPicture.h

FORMS    += mainwindow.ui\
        softwareUpdate.ui\
        mountUSB.ui\
        mainPicture.ui
