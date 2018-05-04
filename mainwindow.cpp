#include "mainwindow.h"
#include <vector>
#include <QPointF>
#include "bezierframe.h"
#include "bsplineframe.h"

using PointLis = vector<QPointF>;

MainWindow::MainWindow(int size, QWidget *parent) : QMainWindow(parent){
    this->resize(size+200,size);
    this->setCentralWidget(tabWidget);

    PointList curve1 {{50.0,50.0},{600.0,600.0},{450.0,750.0},{70.0,650.0},{600.0,200.0}};
    PointList curve2 {{50.0,300.0},{200.0,300.0},{170.0,70.0},{300.0,250.0},{500.0,120.0}};
    PointList curve3 {{700.0,700.0},{550.0,400.0},{700.0,200.0}};
    tabWidget->addTab(new BezierFrame(QSize(size,size),{curve1,curve2,curve3}),QString("Bezier curves"));

    tabWidget->addTab(new BSplineFrame(QSize(size,size),{curve1}),QString("B-Spline curves"));

}
