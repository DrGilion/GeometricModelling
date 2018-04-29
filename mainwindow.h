#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class MainWindow : public QMainWindow{
public:
    explicit MainWindow(int size = 800, QWidget *parent = 0);
    ~MainWindow() = default;
private:
    QTabWidget* tabWidget = new QTabWidget(this);
};

#endif // MAINWINDOW_H
