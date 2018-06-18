TEMPLATE = app
TARGET = GMUebung
CONFIG += c++11
QT += core gui
#QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += gmuebung.cpp \
    mainwindow.cpp \
    axisalignedboundingbox.cpp \
    basicframe.cpp \
    bezierframe.cpp \
    bsplineframe.cpp \
    customslider.cpp
HEADERS += \
    mainwindow.h \
    axisalignedboundingbox.h \
    bezier.h \
    basicframe.h \
    bezierframe.h \
    bsplineframe.h \
    bspline.h \
    util.h \
    customslider.h
