#include "bezierframe.h"
#include "bezier.h"

using namespace bezier;

BezierFrame::BezierFrame(QSize paintAreaSize, PointList2D pControlpoints) : BasicFrame(paintAreaSize),controlPoints(pControlpoints){

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

    this->setLayout(topLayout);
}

void BezierFrame::drawControlPoints(){
    painter->setPen(QPen(Qt::red,pointSize));
    for(auto&& list : controlPoints){
        painter->drawPoints(list.data(),list.size());
    }
}

void BezierFrame::drawControlPointLine(){
    painter->setPen(QPen(Qt::darkGreen,1));
    for(auto&& list : controlPoints){
        for(unsigned int i = 1; i < list.size(); ++i){
            painter->drawLine(list[i-1],list[i]);
        }
    }
}

void BezierFrame::drawCurve(){
    //calculate bezier curve segments
    for(auto&& list : controlPoints){
        calculateBezier(list,curveSegments);
    }

    //draw curve segments
    painter->setPen(QPen(Qt::black,2));
    for(auto&& points : curveSegments){
        for(unsigned int i = 1; i < points.size(); ++i){
            painter->drawLine(points[i-1],points[i]);
        }
    }
}

void BezierFrame::drawIntersections(){
    painter->setPen(QPen(Qt::yellow,pointSize));

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
        painter->drawRect(value);
    }
}

void BezierFrame::drawBoundingBoxes(){
    painter->setPen(QPen(Qt::blue,1));

    for(auto&& value : curveSegments){
        painter->drawRect(AxisAlignedBoundingBox(value).rectangle);
    }
}

void BezierFrame::mousePressEvent(QMouseEvent *event){
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

void BezierFrame::mouseMoveEvent(QMouseEvent *event){
    //std::cout <<"Move: "<< "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    if(currentMovingPoint != NULL){
        currentMovingPoint->setX(event->localPos().x());
        currentMovingPoint->setY(event->localPos().y());
        update();
    }
}

void BezierFrame::mouseReleaseEvent(QMouseEvent *event){
    //std::cout <<"Release: " << "x: " << event->localPos().x() << " y: " << event->localPos().y() << std::endl;
    currentMovingPoint = NULL;
}

void BezierFrame::paintEvent(QPaintEvent* event){
    mPix.fill(Qt::white);

    curveSegments.clear();

    if(drawingControlStructure){
        drawControlPointLine();
        drawControlPoints();
    }
    if(drawingCurve) drawCurve();
    if(drawingBoundingBoxes) drawBoundingBoxes();
    if(drawingIntersections) drawIntersections();
    paintArea->setPixmap(mPix);
}
