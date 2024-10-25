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
    LIBS += -lX11
}
QT += core gui sql svg xml
QT += network

LIBS += -L../update


SOURCES += main.cpp\
        mainwindow.cpp\
        softwareUpdate.cpp\
        databaseUpdate.cpp\
        exportFiles.cpp\
        mainPicture.cpp\
        exportDatabase.cpp

HEADERS  += mainwindow.h\
        softwareUpdate.h\
        databaseUpdate.h\
        exportFiles.h\
        mainPicture.h\
        exportDatabase.h

FORMS    += mainwindow.ui\
        softwareUpdate.ui\
        databaseUpdate.ui\
        exportFiles.ui\
        mainPicture.ui\
        exportDatabase.ui
