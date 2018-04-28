#include "mainwindow.h"
#include "axisalignedboundingbox.h"
#include <iostream>
#include <QLineF>

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

    for(int i = 1; i < size1; i++){
        tempPainter.drawLine(controlPoints1[i-1],controlPoints1[i]);
    }

    for(int i = 1; i < size2; i++){
        tempPainter.drawLine(controlPoints2[i-1],controlPoints2[i]);
    }
}

void MainWindow::drawIntersections(){
    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::yellow,5));

    //calculate intersection points
    vector<QRectF> intersections;
    for(int i = 0; i < curveSegments.size(); i++){
        for(int j = 0; j < curveSegments.size(); j++){
            if(i != j){
                intersect(curveSegments[i],curveSegments[j],intersections);
            }
        }
    }

    for(auto&& value : intersections){
        tempPainter.drawRect(value);
    }
    cout<< "number of intersections: " <<intersections.size() << endl;
}

void MainWindow::drawCurve(){
    plotBezier(controlPoints1);
    plotBezier(controlPoints2);
}

void MainWindow::drawBoundingBoxes(){
    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::blue,1));

    for(auto&& value : curveSegments){
        tempPainter.drawRect(AxisAlignedBoundingBox(value).rectangle);
    }
}

void MainWindow::plotBezier(PointList curve){

    if(isFlat(curve)){
        curveSegments.push_back(curve);
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(Qt::black,2));

        for(int i = 0; i < curve.size()-1; i++){
            tempPainter.drawLine(curve[i],curve[i+1]);
        }

    }else{
        pair<PointList,PointList> points = deCasteljau(curve);
        plotBezier(points.first);
        plotBezier(points.second);
    }
}

bool MainWindow::isFlat(const PointList& points) const{
    double maxFlatness = 1.0;
    for(int i = 1; i< points.size()-1; ++i){
        double flatness = QLineF(points[i+1] - points[i],points[i] - points[i-1]).length();
        if(flatness < maxFlatness){
            maxFlatness = flatness;
        }
    }
    return maxFlatness < epsilon;
}

QPointF MainWindow::lerpPoints(const QPointF& p1,const QPointF& p2, qreal ratio) const{
    return  p1 + ((p2 - p1) * ratio);
}

void MainWindow::intersect(PointList list1, PointList list2,vector<QRectF>& intersections){
    AxisAlignedBoundingBox box1(list1);
    AxisAlignedBoundingBox box2(list2);

    if(box1.intersects(box2)){
        if(!isFlat(list1)){
            //compute composite bezier polygon for first PointList
            pair<PointList,PointList> points = deCasteljau(list1);
            intersect(points.first,list2,intersections);
            intersect(points.second,list2,intersections);
        }else{
            if(!isFlat(list2)){
                //compute composite bezier polygon for second PointList
                pair<PointList,PointList> points = deCasteljau(list2);
                intersect(list1,points.first,intersections);
                intersect(list1,points.second,intersections);
            }else{
                //intersect points
                intersections.push_back(box1.intersected(box2));
            }
        }
    }
}

pair<PointList,PointList> MainWindow::deCasteljau(PointList points)const {
    size_t pointSize = points.size();
    vector<PointList> curvepoints;
    curvepoints.push_back(points);

    for(int i = 0 ; i < pointSize-1; i++){
        curvepoints.push_back(PointList(pointSize));
    }

    for(int iter = 1; iter < pointSize; iter++){
        for(int pos = 0; pos < pointSize - iter; pos++){
            QPointF result = lerpPoints(curvepoints[iter-1][pos], curvepoints[iter-1][pos+1]);
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
    for(auto&& value : controlPoints1){
        if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
           value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingPoint = &value;
            break;
        }
    }
    for(auto&& value : controlPoints2){
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

    curveSegments.clear();

    drawControlPointLine();
    drawControlPoints();
    drawCurve();
    //drawBoundingBoxes();
    drawIntersections();

    painter.drawPixmap(0,0,mPix);
    painter.end();
}
