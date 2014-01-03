#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T14:14:55
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HumanCyborgRelations
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    DownloadDialog.cpp

HEADERS  += MainWindow.hpp \
    DownloadDialog.hpp

FORMS    += MainWindow.ui
