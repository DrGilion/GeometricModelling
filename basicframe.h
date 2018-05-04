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
    constexpr static int pointSize = 15;

    QLabel* paintArea = new QLabel;
    QWidget* optionsWidget = new QWidget;
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    QFormLayout* optionsLayout = new QFormLayout(optionsWidget);

    QPainter* painter = nullptr;
    QPixmap mPix;

    virtual ~BasicFrame();
};

#endif // BASICFRAME_H
