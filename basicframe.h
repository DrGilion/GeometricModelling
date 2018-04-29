#ifndef BASICFRAME_H
#define BASICFRAME_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

class BasicFrame : public QWidget{
public:
    BasicFrame(QSize paintAreaSize);

    QLabel* paintArea = new QLabel;
    QWidget* optionsWidget = new QWidget;
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    QFormLayout* optionsLayout = new QFormLayout(optionsWidget);

    QPainter* painter = NULL;
    QPixmap mPix;

    virtual ~BasicFrame();
};

#endif // BASICFRAME_H
