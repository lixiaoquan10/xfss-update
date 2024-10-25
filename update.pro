#-------------------------------------------------
#
# Project created by QtCreator 2024-02-26T22:22:33
#
#-------------------------------------------------

QT += core gui sql svg xml
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = update
TEMPLATE = app

win32 {
    LIBS += -luser32
}

LIBS += -L../update


SOURCES += main.cpp\
        mainwindow.cpp\
        softwareUpdate.cpp\
        exportFiles.cpp\
        mainPicture.cpp

HEADERS  += mainwindow.h\
        softwareUpdate.h\
        exportFiles.h\
        mainPicture.h

FORMS    += mainwindow.ui\
        softwareUpdate.ui\
        exportFiles.ui\
        mainPicture.ui
