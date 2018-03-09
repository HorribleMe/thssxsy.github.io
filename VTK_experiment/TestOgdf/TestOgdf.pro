#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T17:23:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestOgdf
TEMPLATE = app

INCLUDEPATH += /usr/local/include

LIBS += /usr/local/lib/libCOIN.a\
        /usr/local/lib/libOGDF.a

SOURCES += main.cpp\
        mainwindow.cpp \
    paperconferenceauthorgraph.cpp \
    topicgraph.cpp \
    tgraphwidget.cpp \
    pgraphwidget.cpp

HEADERS  += mainwindow.h \
    paperconferenceauthorgraph.h \
    topicgraph.h \
    tgraphwidget.h \
    pgraphwidget.h

FORMS    += mainwindow.ui \
    tgraphwidget.ui \
    pgraphwidget.ui
