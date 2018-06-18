#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <vector>
#include <QWidget>
#include <QPointF>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

using namespace std;

class CustomSlider : public QWidget{
    Q_OBJECT
public:
    CustomSlider(vector<qreal> handlePositions);

    vector<qreal> handles;

    QLabel* paintArea = new QLabel;

    QPointF* currentMovingKnot = nullptr;

    QPainter* painter = nullptr;
    QPixmap mPix;

    ~CustomSlider() = default;

signals:
    void knotsChanged(vector<qreal> newKnots);
};

#endif // CUSTOMSLIDER_H
