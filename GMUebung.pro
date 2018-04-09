TEMPLATE = app
TARGET = GMUebung
CONFIG += c++11
QT += core gui
#QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += gmuebung.cpp \
    mainwindow.cpp \
    bezierstruct.cpp \
    point.cpp \
    line.cpp
HEADERS += \
    mainwindow.h \
    bezierstruct.h \
    point.h \
    line.h
