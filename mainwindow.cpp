#include "mainwindow.h"
#include "bezier.h"

using namespace bezier;

MainWindow::MainWindow(PointList2D pControlpoints, int size, QWidget *parent) : QMainWindow(parent),windowSize(size), controlPoints(pControlpoints){
    generateGUI();
    mPix = QPixmap(size,size);
    mPix.fill(Qt::white);
    tempPainter = new QPainter(&mPix);
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

    epsilonOption = new QLineEdit(QString::number(EPSILON,'f'));
    QObject::connect(epsilonOption,QLineEdit::returnPressed,this,[&]{
        EPSILON = epsilonOption->text().toDouble();
        update();
    });
    optionsLayout->addRow("Epsilon:",epsilonOption);



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
    tempPainter->setPen(QPen(Qt::red,pointSize));
    for(auto&& list : controlPoints){
        tempPainter->drawPoints(list.data(),list.size());
    }
}

void MainWindow::drawControlPointLine(){
    tempPainter->setPen(QPen(Qt::darkGreen,1));
    for(auto&& list : controlPoints){
        for(unsigned int i = 1; i < list.size(); ++i){
            tempPainter->drawLine(list[i-1],list[i]);
        }
    }
}

void MainWindow::drawCurve(){
    //calculate bezier curve segments
    for(auto&& list : controlPoints){
        calculateBezier(list,curveSegments);
    }

    //draw curve segments
    tempPainter->setPen(QPen(Qt::black,2));
    for(auto&& points : curveSegments){
        for(unsigned int i = 1; i < points.size(); ++i){
            tempPainter->drawLine(points[i-1],points[i]);
        }
    }
}

void MainWindow::drawIntersections(){
    tempPainter->setPen(QPen(Qt::yellow,pointSize));

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
        tempPainter->drawRect(value);
    }
}

void MainWindow::drawBoundingBoxes(){
    tempPainter->setPen(QPen(Qt::blue,1));

    for(auto&& value : curveSegments){
        tempPainter->drawRect(AxisAlignedBoundingBox(value).rectangle);
    }
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
