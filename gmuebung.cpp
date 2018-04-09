#include <QApplication>
#include <QPoint>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

#include "mainwindow.h"

int main(int argc, char** argv){

    QApplication app(argc, argv);
    vector<QPoint> initPoints {QPoint(100,200),QPoint(110,100),QPoint(200,100),QPoint(300,220)};
    MainWindow window(initPoints);
    window.show();


    return app.exec();
}
