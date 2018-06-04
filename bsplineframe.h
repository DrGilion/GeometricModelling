#ifndef BSPLINEFRAME_H
#define BSPLINEFRAME_H

#include "basicframe.h"

#include <vector>
#include <QCheckBox>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLineEdit>

using namespace std;
using PointList = vector<QPointF>;
using PointList2D = vector<PointList>;

class BSplineFrame final: public BasicFrame{
public:
    BSplineFrame(const QSize& paintAreaSize,PointList& pControlPoints );

    void drawControlPoints();
    void drawControlPointLine();
    void drawCurve();

    void drawBezierPoints();
    void drawBezierCurve();

    void insertPoints();

    QCheckBox* controlStructureBox = new QCheckBox();
    QCheckBox* curveBox = new QCheckBox();
    QLineEdit* degreeBox = nullptr;
    QLineEdit* epsilonOption = nullptr;

    bool drawingControlStructure = true;
    bool drawingCurve = true;

    PointList controlPoints;
    PointList2D curveSegments;
    QPointF* currentMovingPoint = nullptr;

    ~BSplineFrame() = default;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);
};

#endif // BSPLINEFRAME_H
