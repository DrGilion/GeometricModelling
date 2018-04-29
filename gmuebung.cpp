#include <QApplication>
#include <QPointF>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

#include "mainwindow.h"

int main(int argc, char** argv){

    QApplication app(argc, argv);
    PointList curve1 {{50.0,50.0},{600.0,600.0},{450.0,750.0},{70.0,650.0},{600.0,200.0}};
    PointList curve2 {{50.0,300.0},{200.0,300.0},{170.0,70.0},{300.0,250.0},{500.0,120.0}};
    PointList curve3 {{700.0,700.0},{550.0,400.0},{700.0,200.0}};
    MainWindow window({curve1,curve2,curve3});
    window.show();

    return app.exec();
}
