#include "bezierstruct.h"

Bezierstruct::Bezierstruct(vector<QPoint>& initialPoints, double subdivisionWeight) : subdivisionWeight(subdivisionWeight){
    curvepoints.push_back(initialPoints);
    for(int i = initialPoints.size()-1; i > 0; i--){
        curvepoints.push_back(vector<QPoint>(i));
    }
    calculateSubdivision();
}

void Bezierstruct::calculateSubdivision(){
    for(int iter = 1; iter < curvepoints[0].size()-1; iter++){
        for(int pos = 0; pos < curvepoints[0].size() - iter; pos++){
            QPoint result(
                (int)((double)(curvepoints[iter-1][pos].x() + curvepoints[iter-1][pos+1].x()) * subdivisionWeight),
                (int)((double)(curvepoints[iter-1][pos].y() + curvepoints[iter-1][pos+1].y()) * subdivisionWeight)
            );
            curvepoints[iter][pos] = result;
        }
    }
}
