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
    constexpr static int pointSize = 10;

    void generateGUI();

    void drawControlPoints();
    void drawControlPointLine();
    void drawIntersections();
    void drawCurve();
    void drawBoundingBoxes();

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

    QLineEdit* epsilonOption = NULL;
    QCheckBox* controlStructureBox = new QCheckBox();
    QCheckBox* curveBox = new QCheckBox();
    QCheckBox* intersectionsBox = new QCheckBox();
    QCheckBox* BoundingBoxesBox = new QCheckBox();

    QPainter painter;
    QPainter* tempPainter = NULL;
    QPixmap mPix;

    PointList2D controlPoints;
    PointList2D curveSegments;
    QPointF* currentMovingPoint = NULL;

    bool drawingControlStructure = true;
    bool drawingCurve = true;
    bool drawingIntersections = true;
    bool drawingBoundingBoxes = false;
};

#endif // MAINWINDOW_H
