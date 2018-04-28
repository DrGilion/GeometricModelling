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
    PointList firstCurve {QPointF(50.0,50.0),QPointF(600.0,600.0),QPointF(450.0,750.0),QPointF(70.0,650.0),QPointF(600.0,200.0)};
    PointList secondCurve {QPointF(50.0,300.0),QPointF(200.0,300.0),QPointF(170.0,70.0),QPointF(300.0,250.0),QPointF(500.0,120.0)};
    MainWindow window(firstCurve,secondCurve);
    window.show();

    return app.exec();
}
