#include "basicframe.h"

BasicFrame::BasicFrame(QSize paintAreaSize) : QWidget(){
    mPix = QPixmap(paintAreaSize);
    painter = new QPainter(&mPix);
    topLayout->addWidget(paintArea);
    topLayout->addWidget(optionsWidget);

    paintArea->setFixedSize(paintAreaSize);
    paintArea->setPixmap(mPix);
    paintArea->setBackgroundRole(QPalette::Base);
    paintArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    optionsWidget->setFixedSize(200,paintAreaSize.height());
}

BasicFrame::~BasicFrame(){
    delete painter;
}
