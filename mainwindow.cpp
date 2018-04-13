#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(PointList controlpoints1,PointList controlpoints2, int size, QWidget *parent) : QMainWindow(parent),windowSize(size),
    controlPoints1(controlpoints1),controlPoints2(controlpoints2){
    setFixedSize(size,size);
    mPix = QPixmap(size,size);
    mPix.fill(Qt::white);
}

void MainWindow::drawControlPoints(){

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::red,10));

    for(auto const& value : controlPoints1){
        tempPainter.drawPoint(value);
    }

    for(auto const& value : controlPoints2){
        tempPainter.drawPoint(value);
    }

}

void MainWindow::drawControlPointLine(){
    size_t size1 = controlPoints1.size();
    size_t size2 = controlPoints2.size();
    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::darkGreen,1));

    for(auto i = 1; i < size1; i++){
        tempPainter.drawLine(controlPoints1[i-1],controlPoints1[i]);
    }

    for(auto i = 1; i < size2; i++){
        tempPainter.drawLine(controlPoints2[i-1],controlPoints2[i]);
    }
}

void MainWindow::drawBezierPolygon(){

}

void MainWindow::drawCurve(){

    plotBezier(controlPoints1,8);
    plotBezier(controlPoints2,8);

}

void MainWindow::plotBezier(PointList curve,int k){
    if(k == 0){
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(Qt::black,2));

        for(int i = 0; i < curve.size()-1; i++){
            tempPainter.drawLine(curve[i],curve[i+1]);
        }

    }else{
        pair<PointList,PointList> points = deCasteljau(curve);
        plotBezier(points.first,k-1);
        plotBezier(points.second,k-1);
    }
}

bool MainWindow::isFlat(PointList points){
    return false;
}

pair<PointList,PointList> MainWindow::deCasteljau(PointList points){
    size_t pointSize = points.size();
    vector<PointList> curvepoints;
    curvepoints.push_back(points);

    for(int i = 0 ; i < pointSize-1; i++){
        curvepoints.push_back(PointList(pointSize));
    }

    for(int iter = 1; iter < pointSize; iter++){
        for(int pos = 0; pos < pointSize - iter; pos++){
            QPointF result(
                (curvepoints[iter-1][pos].x() + curvepoints[iter-1][pos+1].x()) /2.0,
                (curvepoints[iter-1][pos].y() + curvepoints[iter-1][pos+1].y()) /2.0
            );
            curvepoints[iter][pos] = result;
        }
    }

    PointList curve1;
    for(int iter = 0; iter < pointSize; iter++){
        curve1.push_back(curvepoints[iter][0]);
    }

    PointList curve2;
    for(int iter = 0; iter < pointSize; iter++){
       curve2.push_back(curvepoints[curvepoints[0].size()-1-iter][iter]);
    }

    return make_pair(curve1,curve2);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    std::cout <<"Press: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    for(QPointF& value : controlPoints1){
        if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
           value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingPoint = &value;
            break;
        }
    }
    for(QPointF& value : controlPoints2){
        if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
           value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingPoint = &value;
            break;
        }
    }
    //update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    std::cout <<"Move: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    if(currentMovingPoint != NULL){
        currentMovingPoint->setX(event->localPos().x());
        currentMovingPoint->setY(event->localPos().y());
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    std::cout <<"Release: " << "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    currentMovingPoint = NULL;
    //update();
}

void MainWindow::paintEvent(QPaintEvent* event){
    painter.begin(this);
    mPix.fill(Qt::white);

    drawBezierPolygon();
    drawControlPointLine();
    drawControlPoints();
    drawCurve();

    painter.drawPixmap(0,0,mPix);
    painter.end();
}

MainWindow::~MainWindow(){

}
