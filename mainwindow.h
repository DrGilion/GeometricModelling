#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QPointF>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <vector>
#include <utility>

using namespace std;
using PointList = vector<QPointF>;
using PointList2D = vector<PointList>;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(PointList2D pControlpoints,int size = 800, QWidget *parent = 0);

    int windowSize;
    double epsilon = 0.5;
    constexpr static int pointSize = 10;

    void generateGUI();

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
    QLabel* imageLabel = new QLabel;
    QWidget* centralWidget = new QWidget;
    QWidget* optionsWidget = new QWidget;
    QHBoxLayout* topLayout = new QHBoxLayout(centralWidget);
    QFormLayout* optionsLayout = new QFormLayout(optionsWidget);

    QLineEdit* epsilonOption = new QLineEdit(QString::number(epsilon,'f'));
    QCheckBox* controlStructureBox = new QCheckBox();
    QCheckBox* curveBox = new QCheckBox();
    QCheckBox* intersectionsBox = new QCheckBox();
    QCheckBox* BoundingBoxesBox = new QCheckBox();

    QPainter painter;
    QPixmap mPix;

    PointList2D controlPoints;
    PointList2D curveSegments;
    QPointF* currentMovingPoint = NULL;


    bool drawingControlStructure = true;
    bool drawingCurve = true;
    bool drawingIntersections = true;
    bool drawingBoundingBoxes = false;

private slots:

};

#endif // MAINWINDOW_H
