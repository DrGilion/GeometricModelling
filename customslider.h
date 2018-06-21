#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <vector>
#include <QWidget>
#include <QPointF>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QPixmap>

using namespace std;

class CustomSlider final : public QWidget{
    Q_OBJECT
public:
    QSize paintAreaSize = QSize(100,300);

    CustomSlider(vector<qreal> handlePositions,int grade);

    void updateUIKnots();
    vector<qreal> calculateRealKnots();

    vector<qreal> originalKnots;
    int grade;
    vector<QPointF> uiHandles;
    qreal stdHandleDistance;

    QLabel* paintArea = new QLabel;
    QHBoxLayout* topLayout = new QHBoxLayout(this);

    QPointF* currentMovingKnot = nullptr;

    QPainter* painter = nullptr;
    QPixmap mPix;

    ~CustomSlider();

signals:
    void knotsChanged(vector<qreal> newKnots);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);
};

#endif // CUSTOMSLIDER_H
