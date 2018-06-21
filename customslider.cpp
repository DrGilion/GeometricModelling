#include "customslider.h"

CustomSlider::CustomSlider(vector<qreal> handlePositions,int grade) : QWidget(), originalKnots(handlePositions), grade(grade){
    stdHandleDistance = paintAreaSize.height() / (originalKnots.size() - (2*grade));

    mPix = QPixmap(paintAreaSize);
    painter = new QPainter(&mPix);
    topLayout->addWidget(paintArea);

    paintArea->setFixedSize(paintAreaSize);
    paintArea->setPixmap(mPix);
    paintArea->setBackgroundRole(QPalette::Base);
    paintArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    updateUIKnots();
}

void CustomSlider::updateUIKnots(){
    for(int i = 0; i < originalKnots.size() - (2 * grade); ++i ){
        uiHandles.push_back({paintArea->width()/2.0, i * stdHandleDistance});
    }
}

vector<qreal> CustomSlider::calculateRealKnots(){
    vector<qreal> result;
    for(int i = 0; i < originalKnots.size(); ++i ){
        if(i <= grade){
            result.push_back(originalKnots[i]);
        }else if(i >= grade + uiHandles.size()){
            result.push_back(originalKnots[i]);
        }else{
            result.push_back( uiHandles[i-grade].y() / stdHandleDistance);
        }
    }

    return result;
}

CustomSlider::~CustomSlider(){
    delete painter;
}

void CustomSlider::mousePressEvent(QMouseEvent *event){
    int pointSize = 15;
    for(auto&& value : uiHandles){
        if(value.y() - pointSize < event->localPos().y() && value.y() + pointSize > event->localPos().y() ){
            currentMovingKnot = &value;
            break;
        }
    }
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event){
    if(currentMovingKnot != nullptr){
        currentMovingKnot->setY(event->localPos().y());
        update();

        emit knotsChanged(calculateRealKnots());
    }
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *event){
    currentMovingKnot = nullptr;
}

void CustomSlider::paintEvent(QPaintEvent *event){
    mPix.fill(Qt::black);

    painter->setPen(QPen(Qt::white,1));
    painter->drawLine(uiHandles.front(),uiHandles.back());

    painter->setPen(QPen(Qt::red,15));
    for(auto&& handle : uiHandles){
        painter->drawPoint(handle);
    }

    paintArea->setPixmap(mPix);
}

