#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(vector<QPoint> controlpoints1,vector<QPoint> controlpoints2, int size, QWidget *parent) : QMainWindow(parent),windowSize(size),
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

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::darkGreen,1));

    for(auto i = 1; i < controlPoints1.size(); i++){
        tempPainter.drawLine(controlPoints1[i-1],controlPoints1[i]);
    }

    for(auto i = 1; i < controlPoints2.size(); i++){
        tempPainter.drawLine(controlPoints2[i-1],controlPoints2[i]);
    }
}

void MainWindow::drawBezierPolygon(){
    /*glColor3fv(blue);

    glBegin(GL_POLYGON);

    for(int i=0;i<num_points;i++)	{
        glVertex3f((GLfloat)points[i].x,(GLfloat)points[i].y,(GLfloat)points[i].z);
    }

    glEnd();*/

}

void MainWindow::drawCurve(){



    Bezierstruct bezier1(controlPoints1);


    plotBezier(bezier1,6);


    Bezierstruct bezier2(controlPoints2);

    plotBezier(bezier2,6);


}

void MainWindow::plotBezier(Bezierstruct bezier, int k){
    if(k == 0){
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(Qt::black,3));

        auto curve = bezier.getBezierPoints();
        for(int i = 0; i < curve.size()-1; i++){
            tempPainter.drawLine(curve[i],curve[i+1]);
        }

    }else{
        Bezierstruct newbezier(bezier.getBezierPoints());
        plotBezier(Bezierstruct(newbezier.getFirstBezierPartition()),k-1);
        plotBezier(Bezierstruct(newbezier.getSecondBezierPartition()),k-1);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    std::cout <<"Press: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    for(QPoint& value : controlPoints1){
        if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
           value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingPoint = &value;
            break;
        }
    }
    for(QPoint& value : controlPoints2){
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
