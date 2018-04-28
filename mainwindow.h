#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <vector>
#include <utility>

using namespace std;
using PointList = vector<QPointF>;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(PointList controlpoints1,PointList controlpoints2,int size = 800, QWidget *parent = 0);

    constexpr static int pointSize = 10;
    constexpr static double epsilon = 0.05;

    void drawControlPoints();
    void drawControlPointLine();
    void drawIntersections();
    void drawCurve();
    void drawBoundingBoxes();
    void plotBezier(PointList curve);
    pair<PointList,PointList> deCasteljau(PointList curve)const;
    bool isFlat(const PointList& points) const;
    QPointF lerpPoints(const QPointF& p1,const QPointF& p2, qreal ratio = 0.5) const;
    void intersect(PointList list1,PointList list2,vector<QRectF>& intersections);


    ~MainWindow() = default;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    int windowSize;
    QPainter painter;
    QPixmap mPix;

    PointList controlPoints1;
    PointList controlPoints2;
    vector<PointList> curveSegments;
    QPointF* currentMovingPoint = NULL;
};

#endif // MAINWINDOW_H
