#include "bezierstruct.h"

Bezierstruct::Bezierstruct(vector<QPoint> initialPoints, double subdivisionWeight) : subdivisionWeight(subdivisionWeight){
    curvepoints.push_back(vector<QPoint>());
    for(QPoint& point : initialPoints){
        curvepoints[0].push_back(point);
    }

    for(int i = initialPoints.size()-1; i > 0; i--){
        curvepoints.push_back(vector<QPoint>(i));
    }
    calculateSubdivision();
}

void Bezierstruct::calculateSubdivision(){
    for(int iter = 1; iter < curvepoints[0].size(); iter++){
        for(int pos = 0; pos < curvepoints[0].size() - iter; pos++){
            QPoint result(
                (int)((double)(curvepoints[iter-1][pos].x() + curvepoints[iter-1][pos+1].x()) * subdivisionWeight),
                (int)((double)(curvepoints[iter-1][pos].y() + curvepoints[iter-1][pos+1].y()) * subdivisionWeight)
            );
            curvepoints[iter][pos] = result;
        }
    }
}

vector<QPoint> Bezierstruct::getFirstBezierPartition(){
    vector<QPoint> result;
    for(int iter = 0; iter < curvepoints[0].size(); iter++){
        result.push_back(curvepoints[iter][0]);
    }
    return result;
}

vector<QPoint> Bezierstruct::getSecondBezierPartition(){
    vector<QPoint> result;
    for(int iter = 0; iter < curvepoints[0].size(); iter++){
       result.push_back(curvepoints[curvepoints[0].size()-1-iter][iter]);
    }
    return result;
}

vector<QPoint> Bezierstruct::getBezierPoints(){
    vector<QPoint> result;
    for(int iter = 0; iter < curvepoints[0].size(); iter++){
        result.push_back(curvepoints[iter][0]);
    }
    for(int iter = 0; iter < curvepoints[0].size(); iter++){
       result.push_back(curvepoints[curvepoints[0].size()-1-iter][iter]);
    }
    return result;
}
