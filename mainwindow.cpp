#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(vector<QPoint> controlpoints, int size, QWidget *parent) : QMainWindow(parent),windowSize(size),controlPoints(controlpoints),bezierPoints(controlPoints){
    setFixedSize(size,size);
    mPix = QPixmap(size,size);
    mPix.fill(Qt::white);
}

void MainWindow::drawControlPoints(){

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::red,10));

    for(auto const& value : controlPoints){
        tempPainter.drawPoint(value);
    }

}

void MainWindow::drawControlPointLine(){

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::darkGreen,2));

    for(auto i = 1; i < controlPoints.size(); i++){
        tempPainter.drawLine(controlPoints[i-1],controlPoints[i]);
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

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::black,3));

    bezierPoints = Bezierstruct(controlPoints);

    for(int iter = 0; iter < controlPoints.size()-1; iter++){
        tempPainter.drawLine(bezierPoints.curvepoints[iter][0],bezierPoints.curvepoints[iter+1][0]);
    }

    for(int iter = 0; iter < controlPoints.size()-1; iter++){
        tempPainter.drawLine(bezierPoints.curvepoints[controlPoints.size()-1-iter][iter],bezierPoints.curvepoints[controlPoints.size()-2-iter][iter+1]);
    }


}

void MainWindow::mousePressEvent(QMouseEvent *event){
    std::cout <<"Press: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    for(QPoint& value : controlPoints){
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
