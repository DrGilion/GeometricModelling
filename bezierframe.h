#ifndef BEZIERFRAME_H
#define BEZIERFRAME_H

#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSize>
#include <vector>
#include <utility>
#include "basicframe.h"

using namespace std;
using PointList = vector<QPointF>;
using PointList2D = vector<PointList>;

class BezierFrame final: public BasicFrame{
public:
    BezierFrame(const QSize& paintAreaSize, PointList2D pControlpoints);


    void drawControlPoints();
    void drawControlPointLine();
    void drawIntersections();
    void drawCurve();
    void drawBoundingBoxes();

    QLineEdit* epsilonOption = nullptr;
    QCheckBox* controlStructureBox = new QCheckBox();
    QCheckBox* curveBox = new QCheckBox();
    QCheckBox* intersectionsBox = new QCheckBox();
    QCheckBox* BoundingBoxesBox = new QCheckBox();

    bool drawingControlStructure = true;
    bool drawingCurve = true;
    bool drawingIntersections = true;
    bool drawingBoundingBoxes = false;

    PointList2D controlPoints;
    PointList2D curveSegments;

    ~BezierFrame() = default;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);
};

#endif // BEZIERFRAME_H
