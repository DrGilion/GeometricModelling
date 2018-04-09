#include <QApplication>
#include <QPushButton>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

#include "mainwindow.h"

using namespace std;

int main(int argc, char** argv){

    QApplication app(argc, argv);
    MainWindow window;
    window.show();


    return app.exec();
}
