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
using PointList2D = vector<PointList>;


namespace bspline {
    static int GRADE = 1;

    void deBoor(const PointList& points,PointList2D& resultList){
        size_t pointSize = points.size();
        vector<qreal> knotpoints;

        unsigned int iter = GRADE + pointSize +1;

        //beginning padding
        for(unsigned int i = 0 ; i < GRADE; i++){
            knotpoints.push_back(0);
        }

        unsigned int counter = 0;
        for(counter = 0 ; counter < iter; counter++){
            knotpoints.push_back(counter);
        }

        //end padding
        for(unsigned int i = 0 ; i < GRADE; i++){
            knotpoints.push_back(counter);
        }

        for(auto val : knotpoints){
            cout << "value: " << val << endl;
        }

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
0 0 0 0 1 2 3 3 3 3

0 0 0 0 1 2 3 3 3 3*/
