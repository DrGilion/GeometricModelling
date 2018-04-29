#include "mainwindow.h"
#include "axisalignedboundingbox.h"
#include <iostream>
#include <QLineF>

MainWindow::MainWindow(PointList2D pControlpoints, int size, QWidget *parent) : QMainWindow(parent),windowSize(size), controlPoints(pControlpoints){
    generateGUI();
    mPix = QPixmap(size,size);
    mPix.fill(Qt::white);
}

void MainWindow::generateGUI(){
    this->resize(windowSize+200,windowSize);
    this->setCentralWidget(centralWidget);

    topLayout->addWidget(imageLabel);
    topLayout->addWidget(optionsWidget);

    imageLabel->setFixedSize(windowSize,windowSize);
    imageLabel->setPixmap(mPix);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    optionsWidget->setFixedSize(200,windowSize);

    optionsLayout->addRow("Epsilon:",epsilonOption);
    QObject::connect(epsilonOption,QLineEdit::returnPressed,this,[&]{
        epsilon = epsilonOption->text().toDouble();
        update();
    });

    controlStructureBox->setChecked(drawingControlStructure);
    optionsLayout->addRow("draw control structure :",controlStructureBox );
    QObject::connect(controlStructureBox,QCheckBox::toggled,this,[&](bool val){
        drawingControlStructure = val;
        update();
    });

    curveBox->setChecked(drawingCurve);
    optionsLayout->addRow("draw curve :",curveBox );
    QObject::connect(curveBox,QCheckBox::toggled,this,[&](bool val){
        drawingCurve = val;
        update();
    });

    intersectionsBox->setChecked(drawingIntersections);
    optionsLayout->addRow("draw intersections :",intersectionsBox );
    QObject::connect(intersectionsBox,QCheckBox::toggled,this,[&](bool val){
        drawingIntersections = val;
        update();
    });

    BoundingBoxesBox->setChecked(drawingBoundingBoxes);
    optionsLayout->addRow("draw bounding boxes :",BoundingBoxesBox );
    QObject::connect(BoundingBoxesBox,QCheckBox::toggled,this,[&](bool val){
        drawingBoundingBoxes = val;
        update();
    });
}

void MainWindow::drawControlPoints(){

    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::red,10));

    for(auto&& list : controlPoints){
        for(auto&& point : list){
            tempPainter.drawPoint(point);
        }
    }

}

void MainWindow::drawControlPointLine(){
    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::darkGreen,1));

    for(auto&& list : controlPoints){
        for(unsigned int i = 1; i < list.size(); ++i){
            tempPainter.drawLine(list[i-1],list[i]);
        }
    }
}

void MainWindow::drawIntersections(){
    QPainter tempPainter(&mPix);
    tempPainter.setPen(QPen(Qt::yellow,5));

    //calculate intersection points
    vector<QRectF> intersections;
    for(unsigned i = 0; i < curveSegments.size(); ++i){
        for(unsigned int j = 0; j < curveSegments.size(); ++j){
            if(i != j){
                intersect(curveSegments[i],curveSegments[j],intersections);
            }
        }
    }
    //draw intersections
    for(auto&& value : intersections){
        tempPainter.drawRect(value);
    }
}

void MainWindow::drawCurve(){
    for(auto&& list : controlPoints){
        plotBezier(list);
    }
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

        for(unsigned int i = 0; i < curve.size()-1; i++){
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
    for(unsigned int i = 1; i< points.size()-1; ++i){
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
    PointList2D curvepoints;
    curvepoints.push_back(points);

    for(unsigned int i = 0 ; i < pointSize-1; i++){
        curvepoints.push_back(PointList(pointSize));
    }

    for(unsigned int iter = 1; iter < pointSize; iter++){
        for(unsigned int pos = 0; pos < pointSize - iter; pos++){
            QPointF result = lerpPoints(curvepoints[iter-1][pos], curvepoints[iter-1][pos+1]);
            curvepoints[iter][pos] = result;
        }
    }

    PointList curve1;
    for(unsigned int iter = 0; iter < pointSize; iter++){
        curve1.push_back(curvepoints[iter][0]);
    }

    PointList curve2;
    for(unsigned int iter = 0; iter < pointSize; iter++){
       curve2.push_back(curvepoints[curvepoints[0].size()-1-iter][iter]);
    }

    return make_pair(curve1,curve2);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    //std::cout <<"Press: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    for(auto&& list : controlPoints){
        for(auto&& value : list){
            if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
               value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
                currentMovingPoint = &value;
                break;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    //std::cout <<"Move: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    if(currentMovingPoint != NULL){
        currentMovingPoint->setX(event->localPos().x());
        currentMovingPoint->setY(event->localPos().y());
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    //std::cout <<"Release: " << "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    currentMovingPoint = NULL;
}

void MainWindow::paintEvent(QPaintEvent* event){
    painter.begin(this);
    mPix.fill(Qt::white);

    curveSegments.clear();

    if(drawingControlStructure){
        drawControlPointLine();
        drawControlPoints();
    }
    if(drawingCurve) drawCurve();
    if(drawingBoundingBoxes) drawBoundingBoxes();
    if(drawingIntersections) drawIntersections();

    painter.drawPixmap(0,0,mPix);
    painter.end();
}
