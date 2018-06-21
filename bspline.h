#ifndef BSPLINE
#define BSPLINE

#include <vector>
#include <QPointF>
#include <utility>
#include <iostream>

#include "bezier.h"

using namespace std;
using namespace bezier;
using PointList = vector<QPointF>;
using FloatList = vector<qreal>;
using PointList2D = vector<PointList>;


namespace bspline {
    static int GRADE = 3;

    FloatList calculateKnots(const PointList& points){
        size_t pointSize = points.size();
        FloatList knotpoints;

        unsigned int maxIter = GRADE + pointSize +1;

        int i = 0;
        //beginning padding
        for(; i < GRADE; i++){
            knotpoints.push_back(0);
        }

        int num = 0;
        for(; i < pointSize; i++){
            knotpoints.push_back(num++);
        }

        //end padding
        for(; i < maxIter; i++){
            knotpoints.push_back(num);
        }

        return knotpoints;
    }


    qreal alpha(int i, int j, qreal t, const FloatList &x){
        return (t - x[i]) / (x[i + GRADE - j + 1] - x[i]);
    }


    QPointF d(const QPointF& d0, const QPointF& d1,qreal alpha){
        return (1 - alpha) * d0 + alpha * d1;
    }


    int largestTIndex(const FloatList& x) {
        qreal currNum = x[0];
        int counter = 1;

        for (int i = 1; i < x.size(); ++i) {
            if(x[i] == currNum) {
                counter++;
            } else {
                if(counter < GRADE) {
                    return i - 1;
                } else {
                    counter = 1;
                    currNum = x[i];
                }
            }
        }

        return -1;
    }

    PointList deBoor(int r, float t, const FloatList& X, const PointList &currPoints) {
        PointList resultPoints = PointList(currPoints.size() + 1);

        int startIndex = r - GRADE;

        for (int i = 0; i < resultPoints.size(); ++i) {
            if(i <= startIndex) {
                resultPoints[i] = currPoints[i];
            } else if(i >= r) {
                resultPoints[i] = currPoints[i - 1];
            } else {
                resultPoints[i] = d(currPoints[i - 1], currPoints[i], alpha(i, 0, t, X));
            }
        }

        return resultPoints;
    }

    void calculateDeBoor(const PointList& controlPoints,FloatList& knots,PointList2D& resultList){
        FloatList x = knots;
        PointList intermediateResult = controlPoints;

        int r = largestTIndex(x);

        while (r != -1) {
            qreal t = (x[r] + x[r - 1]) / 2;
            intermediateResult = deBoor(r, t, x, intermediateResult);

            qreal xr = x[r];
            x.insert(x.begin() + r, xr);
            r = largestTIndex(x);
        }

        resultList.clear();
        size_t numBezier = (intermediateResult.size() - 1) / GRADE;
        for (int i = 0; i < numBezier; ++i) {
            PointList tmpControlPoints = PointList(intermediateResult.begin() + i * GRADE, intermediateResult.begin() + (i * GRADE) + GRADE + 1);
            calculateBezier(tmpControlPoints,resultList);
        }

    }
}



#endif // BSPLINE
/*n = 3 m = 6

0 0 0 0 1 2 3 3 3 3*/
