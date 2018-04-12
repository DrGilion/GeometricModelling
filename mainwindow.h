#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bezierstruct.h"

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QPoint>
#include <vector>

using namespace std;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(vector<QPoint> controlpoints1,vector<QPoint> controlpoints2,int size = 800, QWidget *parent = 0);

    const int pointSize = 10;

    void drawControlPoints();
    void drawControlPointLine();
    void drawBezierPolygon();
    void drawCurve();
    void plotBezier(Bezierstruct bezier,int k);

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

    vector<QPoint> controlPoints1;
    vector<QPoint> controlPoints2;
    QPoint* currentMovingPoint = NULL;
};

#endif // MAINWINDOW_H
