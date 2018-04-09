#ifndef BEZIERSTRUCT_H
#define BEZIERSTRUCT_H

#include <vector>
#include <QPoint>

using namespace std;

class Bezierstruct{
public:
    Bezierstruct(vector<QPoint>& initialPoints, double subdivisionWeight = 0.5);
    void calculateSubdivision();

    double subdivisionWeight;
    vector<vector<QPoint>> curvepoints;
};

#endif // BEZIERSTRUCT_H
