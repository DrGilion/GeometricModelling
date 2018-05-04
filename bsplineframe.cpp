#include "bsplineframe.h"

#include "util.h"

BSplineFrame::BSplineFrame(const QSize& paintAreaSize,PointList& pControlPoints) : BasicFrame(paintAreaSize),controlPoints(pControlPoints) {
    controlStructureBox->setChecked(drawingControlStructure);
    optionsLayout->addRow("draw control structure :",controlStructureBox );
    QObject::connect(controlStructureBox,&QCheckBox::toggled,this,[&](bool val){
        drawingControlStructure = val;
        update();
    });

    curveBox->setChecked(drawingCurve);
    optionsLayout->addRow("draw curve :",curveBox );
    QObject::connect(curveBox,&QCheckBox::toggled,this,[&](bool val){
        drawingCurve = val;
        update();
    });

    degreeBox = new QLineEdit(QString::number(degree));
    optionsLayout->addRow("degree :",degreeBox );
    QObject::connect(degreeBox,&QLineEdit::returnPressed,this,[&]{
        degree = gmutil::clamp(degreeBox->text().toInt(),2,controlPoints.size()-1);
        degreeBox->setText(QString::number(degree));
        update();
    });

    this->setLayout(topLayout);
}

void BSplineFrame::drawControlPoints(){
    painter->setPen(QPen(Qt::red,pointSize));

    painter->drawPoints(controlPoints.data(),controlPoints.size());
}

void BSplineFrame::drawControlPointLine(){
    painter->setPen(QPen(Qt::darkGreen,1));

    for(unsigned int i = 1; i < controlPoints.size(); ++i){
        painter->drawLine(controlPoints[i-1],controlPoints[i]);
    }
}

void BSplineFrame::drawCurve(){

}

void BSplineFrame::mousePressEvent(QMouseEvent *event){
    for(auto&& value : controlPoints){
        if(value.x() - pointSize < event->localPos().x() && value.x() + pointSize > event->localPos().x() &&
           value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingPoint = &value;
            break;
        }
    }
}

void BSplineFrame::mouseMoveEvent(QMouseEvent *event){
    if(currentMovingPoint != nullptr){
        currentMovingPoint->setX(event->localPos().x());
        currentMovingPoint->setY(event->localPos().y());
        update();
    }
}

void BSplineFrame::mouseReleaseEvent(QMouseEvent *event){
    currentMovingPoint = nullptr;
}

void BSplineFrame::paintEvent(QPaintEvent *event){
    mPix.fill(Qt::white);

    if(drawingControlStructure){
        drawControlPointLine();
        drawControlPoints();
    }
    if(drawingCurve) drawCurve();

    paintArea->setPixmap(mPix);
}
