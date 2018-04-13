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
    constexpr static double epsilon = 0.001;

    void drawControlPoints();
    void drawControlPointLine();
    void drawBezierPolygon();
    void drawCurve();
    void plotBezier(PointList,int k);
    pair<PointList,PointList> deCasteljau(PointList curve);
    bool isFlat(PointList points);


    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    int windowSize;
    QPainter painter;
    QPixmap mPix;

    PointList controlPoints1;
    PointList controlPoints2;
    QPointF* currentMovingPoint = NULL;
};

#endif // MAINWINDOW_H
