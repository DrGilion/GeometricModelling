TEMPLATE = app
TARGET = GMUebung
CONFIG += c++11
QT += core gui
#QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += gmuebung.cpp \
    mainwindow.cpp \
    bezierstruct.cpp \
    axisalignedboundingbox.cpp
HEADERS += \
    mainwindow.h \
    bezierstruct.h \
    axisalignedboundingbox.h
