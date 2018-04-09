#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    const float white[] = {1.0, 1.0, 1.0};
    const float black[] = {0.0, 0.0, 0.0};
    const float red[] = {1.0, 0.0, 0.0};
    const float green[] = {0.0, 1.0, 0.0};
    const float blue[] = {0.0, 0.0, 1.0};

    bool mousePressed;
    bool drawStarted;
    const int pointSize = 10;

    void drawControlPoints();
    void drawControlPointLine();
    void drawBezierPolygon();
    void drawCurve();


    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:

public slots:

private:
    QPainter painter;
    QPixmap mPix;
};

#endif // MAINWINDOW_H
