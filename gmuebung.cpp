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
    vector<QPoint> firstCurve {QPoint(50,50),QPoint(600,600),QPoint(450,750),QPoint(70,650),QPoint(600,200)};
    vector<QPoint> secondCurve {QPoint(50,300),QPoint(200,300),QPoint(170,70),QPoint(300,250),QPoint(500,120)};
    MainWindow window(firstCurve,secondCurve);
    window.show();

    return app.exec();
}
