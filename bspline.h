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

        for(auto val : knotpoints){
            cout << "value: " << val << endl;
        }

        return knotpoints;
    }

    void calculateDeBoor(const PointList& points,PointList2D& resultList){
        FloatList knots = calculateKnots(points);

        /*for(unsigned int pos = 0; pos < pointSize; pos++){
            //check index before calculating
            if(true) {

            }

            //calculate delta
            double ratio = a /b;

            QPointF result = gmutil::lerpPoints(knotpoints[iter-1][pos], knotpoints[iter-1][pos+1],ratio);
            knotpoints[iter][pos] = result;
        }*/

    }
}



#endif // BSPLINE
/*n = 3 m = 6

0 0 0 0 1 2 3 3 3 3*/
