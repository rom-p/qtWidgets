QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtWidgetSample
TEMPLATE = app

INCLUDEPATH += ../src

SOURCES += main.cpp\
           mainwindow.cpp\
           ../src/qanimatedtimer.cpp\
           ../src/qvumeter.cpp

HEADERS += mainwindow.h\
           ../src/qanimatedtimer.h\
           ../src/qvumeter.h

FORMS   += mainwindow.ui
